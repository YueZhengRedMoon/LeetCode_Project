#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Solution
{
public:
    std::vector<int> countMentions(int numberOfUsers, std::vector<std::vector<std::string>>& events)
    {
        // 按照时间戳排序，若时间戳相同，则优先处理离线时间
        std::sort(events.begin(), events.end(),
                  [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            int timestampA = std::stoi(a[1]), timestampB = std::stoi(b[1]);
            if (timestampA == timestampB)
                return a[0] == "OFFLINE";
            else
                return timestampA < timestampB;
        });

        std::vector<int> ans(numberOfUsers, 0);
        std::vector<bool> isOnline(numberOfUsers, true);
        std::queue<std::pair<int, int>> loginQueue; // 登录队列：<用户id, 登录时间戳>
        int mentionAll = 0; // 提及所有用户的次数
        for (std::vector<std::string>& e : events)
        {
            int timestamp = std::stoi(e[1]);

            // 离线的用户重新上线
            while (!loginQueue.empty() && loginQueue.front().second <= timestamp)
            {
                isOnline[loginQueue.front().first] = true;
                loginQueue.pop();
            }

            if (e[0] == "MESSAGE")
            {
                if (e[2] == "ALL")
                {
                    ++mentionAll;
                }
                else if (e[2] == "HERE")
                {
                    for (int i = 0; i < numberOfUsers; ++i)
                    {
                        if (isOnline[i])
                            ++ans[i];
                    }
                }
                else
                {
                    int id = 0;
                    std::string& s = e[2];
                    s.push_back('i');   // 在末尾添加上'i'以方便统一处理
                    for (int i = 2; i < s.size(); ++i)
                    {
                        if (std::isdigit(s[i]))
                        {
                            id = id * 10 + (s[i] - '0');
                        }
                        else if (s[i] == 'i')
                        {
                            ++ans[id];
                            id = 0;
                        }
                    }
                }
            }
            else    // e[0] == "OFFLINE"
            {
                int id = std::stoi(e[2]);
                isOnline[id] = false;
                loginQueue.emplace(id, timestamp + 60);
            }
        }
        if (mentionAll)
        {
            for (int i = 0; i < numberOfUsers; ++i)
            {
                ans[i] += mentionAll;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
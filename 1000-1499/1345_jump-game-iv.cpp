#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minJumps(std::vector<int>& arr)
    {
        std::unordered_map<int, std::vector<int>> group;
        int n = arr.size();
        for (int i = 0; i < n; ++i)
        {
            group[arr[i]].push_back(i);
        }
        std::vector<bool> visit(n, false);
        visit[0] = true;
        std::vector<int> queue({0});
        int ans = 0;
        while (true)
        {
            std::vector<int> temp;
            for (int i : queue)
            {
                if (i == n - 1)
                {
                    return ans;
                }

                int x = arr[i];
                auto it = group.find(x);
                if (it != group.end())
                {
                    for (int j : it->second)
                    {
                        if (!visit[j])
                        {
                            visit[j] = true;
                            temp.push_back(j);
                        }
                    }
                    group.erase(it);    // 删除，避免重复访问
                }

                if (i + 1 < n && !visit[i + 1])
                {
                    temp.push_back(i + 1);
                    visit[i + 1] = true;
                }
                if (i - 1 >= 0 && !visit[i - 1])
                {
                    temp.push_back(i - 1);
                    visit[i - 1] = true;
                }
            }
            std::swap(queue, temp);
            ++ans;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
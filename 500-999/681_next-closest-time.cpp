#include <iostream>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    std::string nextClosestTime(std::string time)
    {
        std::unordered_set<int> digits({time[0] - '0', time[1] - '0', time[3] - '0', time[4] - '0'});
        std::string ans = time;
        int minDT = 24 * 60; // 到下一个最近时刻的时间间隔
        int curH = (time[0] - '0') * 10 + (time[1] - '0'), curM = (time[3] - '0') * 10 + (time[4] - '0');
        int cur = curH * 60 + curM;
        int nextTime[4];
        std::function<void(int)> dfs = [&](int i) {
            if (i == 2 && (nextTime[0] * 10 + nextTime[1] > 24))
                return;
            if (i == 4)
            {
                int m = nextTime[2] * 10 + nextTime[3];
                if (m >= 60)
                    return;
                int h = nextTime[0] * 10 + nextTime[1];

                int dT;
                if (h > curH || (h == curH && m > curM))    // 下个时刻在今天
                {
                    dT =  h * 60 + m - cur;
                }
                else    // 下个时刻在明天
                {
                    dT = 24 * 60 + h * 60 + m - cur;
                }
                if (dT < minDT)
                {
                    minDT = dT;
                    updateAns(ans, nextTime);
                }
                return;
            }
            for (int d : digits)
            {
                nextTime[i] = d;
                dfs(i + 1);
            }
        };
        dfs(0);
        return ans;
    }

private:
    void updateAns(std::string& ans, int nextTime[4])
    {
        ans[0] = nextTime[0] + '0';
        ans[1] = nextTime[1] + '0';
        ans[3] = nextTime[2] + '0';
        ans[4] = nextTime[3] + '0';
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

class Solution
{
public:
    int minCost(std::string colors, std::vector<int>& neededTime)
    {
        int n = colors.size(), ans = 0;
        int sumTime = neededTime[0];    // 连续相同颜色气球的移除时间之和
        int maxTime = neededTime[0];    // 连续相同颜色气球中所需最多的移除时间
        bool isContinuous = false;      // 当前气球的颜色是否是连续相同的

        for (int i = 1; i < n; ++i)
        {
            if (colors[i] == colors[i - 1]) // 当前气球的颜色与前一个气球的颜色相同
            {
                sumTime += neededTime[i];
                if (neededTime[i] > maxTime)
                    maxTime = neededTime[i];
                isContinuous = true;
            }
            else    // 当前气球的颜色与前一个气球的颜色不同
            {
                // 此前气球的颜色是连续相同的，仅保留移除时间最大的气球，将其他气球移除
                if (isContinuous)
                {
                    ans += sumTime - maxTime;
                }
                maxTime = neededTime[i];
                sumTime = neededTime[i];
                isContinuous = false;
            }
        }
        if (isContinuous)
        {
            ans += sumTime - maxTime;
        }

        return ans;
    }
};

// 错误
class WrongSolution
{
public:
    int minCost(std::string colors, std::vector<int>& neededTime)
    {
        int n = colors.size();

        // f[i]:将colors[0,i)变成彩色所需的最少时间
        // f[0]=0:绳子上没有气球，假设其满足条件，无需时间
        // f[1]=0:绳子上只有一个气球，已经满足条件，无需时间
        int f[2]{0, 0};

        for (int i = 2; i <= n; ++i)
        {
            int cur = i - 1;    // 当前气球的序号
            int pre = i - 2;    // 前一个气球的序号

            // 当前气球的颜色与前一个气球的颜色相同，需要移除其中一个
            if (colors[cur] == colors[pre])
            {
                f[i % 2] = std::min(f[(i - 1) % 2] + neededTime[cur],   // 移除当前的气球
                                    f[i % 2] + neededTime[pre]);        // 移除前一个气球
            }
            // 当前气球的颜色与前一个气球的颜色不同，无需移除
            else
            {
                f[i % 2] = f[(i - 1) % 2];
            }
        }

        return f[n % 2];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
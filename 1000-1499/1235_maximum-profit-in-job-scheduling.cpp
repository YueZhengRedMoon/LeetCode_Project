#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit)
    {
        int n = startTime.size();

        // 按照工作的结束时间从小到大排序
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int i, int j) -> bool {return endTime[i] < endTime[j];});

        // f[i]:在idx[0]到idx[i-1]中可以拿到的最大收益,f[0]=0
        std::vector<int> f(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            // 找到第一份结束时间>startTime[idx[i-1]]的工作
            int left = 0, right = i, j = -1, start = startTime[idx[i - 1]];
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (endTime[idx[mid]] > start)
                {
                    j = mid - 1;
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }

            f[i] = std::max(f[i - 1], f[j + 1] + profit[idx[i - 1]]);
        }

        return f[n];
    }
};

class Solution2
{
public:
    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit)
    {
        int n = startTime.size();
        std::vector<std::array<int, 3>> jobs(n);
        for (int i = 0; i < n; ++i)
        {
            jobs[i] = {endTime[i], startTime[i], profit[i]};
        }
        // 按照结束时间从小到大排序
        std::sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) -> bool {return a[0] < b[0];});

        std::vector<int> f(n + 1, 0);   // f[i]:工作按结束时间排序后，选择jobs[0,i)能取得的最大收益
        for (int i = 0; i < n; ++i)
        {
            // 找到第一个结束时间>当前第i份工作开始时间的工作
            int j = std::upper_bound(jobs.begin(), jobs.begin() + i, std::array<int, 3>{jobs[i][1], INT_MAX}) - jobs.begin();
            // f[i]:不选第i份工作
            // f[j]+jobs[i][2]:选第i份工作, endTime[j] <= startTime[i]
            f[i + 1] = std::max(f[i], f[j] + jobs[i][2]);
        }

        return f[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

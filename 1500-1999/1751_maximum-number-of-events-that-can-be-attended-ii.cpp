#include <iostream>
#include <vector>
#include <algorithm>

// 超时
class Solution
{
public:
    int maxValue(std::vector<std::vector<int>>& events, int k)
    {
        // 将会议按照结束时间升序排序
        std::sort(events.begin(), events.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });

        int n = events.size();
        int ans = 0;

        // f[i][j]:在event[0, j)中参加i+1个会议最多可以获得多少价值，如果为-1，则表示无法在event[0, j)中参加i+1个会议
        std::vector<std::vector<int>> f(k + 1, std::vector<int>(n + 1, -1));
        for (int j = 0; j <= n; ++j)
        {
            // 参加0个会议的价值为0
            f[0][j] = 0;

            if (j > 0)
            {
                f[1][j] = std::max(events[j - 1][2], f[1][j - 1]);
                if (f[1][j] > ans)
                    ans = f[1][j];
            }
        }

        for (int i = 2; i <= k; ++i)
        {
            for (int j = i; j <= n; ++j)
            {
                int startDay = events[j - 1][0], value = events[j - 1][2];

                // 参加第j个会议（序号为j-1）
                int _j = j - 1;
                while (_j >= 1)
                {
                    if (events[_j - 1][1] < startDay && f[i - 1][_j] >= 0)
                    {
                        f[i][j] = std::max(f[i][j], f[i - 1][_j] + value);
                    }
                    --_j;
                }

                // 不参加第j个会议，在events[0, j-1)中参加i个会议
                f[i][j] = std::max(f[i][j], f[i - 1][j]);

                if (f[i][j] > ans)
                    ans = f[i][j];
            }
        }

        for (int i = 0; i <= k; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                std::cout << f[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        return ans;
    }
};

class Solution2
{
public:
    int maxValue(std::vector<std::vector<int>>& events, int k)
    {
        if (k == 1)
        {
            return (*std::max_element(events.begin(), events.end(), [](const auto& a, const auto& b) {
                return a[2] < b[2];
            }))[2];
        }

        // 将会议按照结束时间升序排序
        std::sort(events.begin(), events.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });

        int n = events.size();
        // f[i][j]:在event[0, i)中最多参加j个会议最多可以获得多少价值
        std::vector<std::vector<int>> f(n + 1, std::vector<int>(k + 1));

        for (int i = 0; i < n; ++i)
        {
            int startDay = events[i][0], value = events[i][2];

            // 使用二分查找，找到结束日期最早，同时结束日期 >= 当前会议开始日期的会议p
            int left = 0, right = i + 1, p = 0;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (events[mid][1] >= startDay) // events[mid].endDay >= startDay
                {
                    p = mid;
                    right = mid;
                }
                else    // events[mid].endDay < startDay
                {
                    left = mid + 1;
                }
            }

            for (int j = 1; j <= k; ++j)
            {
                f[i + 1][j] = std::max(f[i][j], f[p][j - 1] + value);
            }
        }

        return f[n][k];
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::vector<int>> events = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}};
    int k = 3;
    int ans = solution.maxValue(events, k);
    std::cout << ans << std::endl;
    return 0;
}

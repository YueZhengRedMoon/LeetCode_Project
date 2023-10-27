#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int assignBikes(std::vector<std::vector<int>> &workers, std::vector<std::vector<int>> &bikes)
    {
        const int n = workers.size(), m = bikes.size();
        const int inf = std::numeric_limits<int>::max();
        std::vector<std::vector<int>> dp(1 << n, std::vector<int>(1 << m, inf));
        dp[0][0] = 0;

        auto manhattan = [&](int w, int b) -> int {
            return std::abs(workers[w][0] - bikes[b][0]) + std::abs(workers[w][1] - bikes[b][1]);
        };

        for (int i = 0; i < (1 << n); ++i)
        {
            for (int j = 0; j < (1 << m); ++j)
            {
                int workerCount = calcOneCount(i);
                int bikeCount = calcOneCount(j);
                if (bikeCount != workerCount)
                    continue;

                for (int w = 0; (i >> w) > 0; ++w)
                {
                    if ((i & (1 << w)) == 0)
                        continue;
                    int lastWorkerStatus = i & ~(1 << w);
                    for (int b = 0; (j >> b) > 0; ++b)
                    {
                        if ((j & (1 << b)) == 0)
                            continue;
                        int lastBikeStatus = j & ~(1 << b);

                        if (dp[lastWorkerStatus][lastBikeStatus] != inf)
                        {
                            dp[i][j] = std::min(dp[i][j], dp[lastWorkerStatus][lastBikeStatus] + manhattan(w, b));
                        }
                    }
                }
            }
        }

        int ans = dp[(1 << n) - 1][(1 << n) - 1];
        for (int j = (1 << n); j < (1 << m); ++j)
        {
            ans = std::min(ans, dp[(1 << n) - 1][j]);
        }
        return ans;
    }

private:
    int calcOneCount(int num)
    {
        int count = 0;
        while (num > 0)
        {
            count += (num & 1);
            num >>= 1;
        }
        return count;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> workers1 = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    std::vector<std::vector<int>> bikes1 = {{0, 999}, {1, 999}, {2, 999}, {3, 999}, {4, 999}};
    int result1 = solution.assignBikes(workers1, bikes1);
    std::cout << result1 << std::endl;

    std::vector<std::vector<int>> workers2 = {{0, 0}, {2, 1}};
    std::vector<std::vector<int>> bikes2 = {{1, 2}, {3, 3}};
    int result2 = solution.assignBikes(workers2, bikes2);
    std::cout << result2 << std::endl;

    std::vector<std::vector<int>> workers3 = {{239, 904}, {191, 103}, {260,117}, {86, 78}, {747, 62}};
    std::vector<std::vector<int>> bikes3 = {{660, 8}, {431, 772}, {78, 576}, {894, 481}, {451, 730}, {155, 28}};
    int result3 = solution.assignBikes(workers3, bikes3);
    std::cout << result3 << std::endl;
    return 0;
}

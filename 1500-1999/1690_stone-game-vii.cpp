#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int stoneGameVII(std::vector<int> &stones)
    {
        int n = stones.size();
        std::vector<int> prefix(n + 1);
        std::partial_sum(stones.begin(), stones.end(), prefix.begin() + 1);

        auto rangeSum = [&prefix](int i, int j) -> int {return prefix[j + 1] - prefix[i];};

        // dp[i][j]:在stones[i,j]中先手得分减去后手得分的最大值
        std::vector<int> dp(n);
        for (int i = n - 2; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                dp[j] = std::max(rangeSum(i + 1, j) - dp[j], rangeSum(i, j - 1) - dp[j - 1]);
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

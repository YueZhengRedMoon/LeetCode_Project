#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int numSquares(int n)
    {
        std::vector<int> squares;
        squares.reserve(100);

        for (int i = 1; i * i <= n; ++i)
        {
            squares.push_back(i * i);
        }
        squares.shrink_to_fit();

        // dp[j]:和为j的完全平方数的最少数量
        std::vector<int> dp(n + 1, std::numeric_limits<int>::max() - 1);
        dp[0] = 0;

        for (int i = 0; i < squares.size(); ++i)
        {
            for (int j = squares[i]; j <= n; ++j)
            {
                dp[j] = std::min(dp[j], dp[j - squares[i]] + 1);
            }
        }

        return dp[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

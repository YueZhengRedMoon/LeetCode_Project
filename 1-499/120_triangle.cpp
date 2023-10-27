#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int minimumTotal(std::vector<std::vector<int>> &triangle)
    {
        int n = triangle.back().size();
        std::vector<int> dp(n, std::numeric_limits<int>::max());
        dp[0] = triangle[0][0];

        for (int i = 1; i < triangle.size(); ++i)
        {
            for (int j = triangle[i].size() - 1; j >= 1; --j)
            {
                dp[j] = std::min(dp[j], dp[j - 1]) + triangle[i][j];
            }
            dp[0] += triangle[i][0];
        }

        int ans = dp[0];
        for (int i = 1; i < n; ++i)
        {
            if (dp[i] < ans)
            {
                ans = dp[i];
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

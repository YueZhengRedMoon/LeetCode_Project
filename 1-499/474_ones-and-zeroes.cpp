#include <iostream>
#include <vector>
#include <string>

class Solution
{
public:
    int findMaxForm(std::vector<std::string> &strs, int m, int n)
    {
        // dp[i][j]:最多有i个0，j个1的的最大子集的长度
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        std::vector<int> zeroNums(strs.size(), 0);
        std::vector<int> oneNums(strs.size(), 0);

        for (int i = 0; i < strs.size(); ++i)
        {
            for (char c : strs[i])
            {
                if (c == '0')
                {
                    ++zeroNums[i];
                }
                else
                {
                    ++oneNums[i];
                }
            }
        }

        for (int k = 0; k < strs.size(); ++k)
        {
            for (int i = m; i >= zeroNums[k]; --i)
            {
                for (int j = n; j >= oneNums[k]; --j)
                {
                    dp[i][j] = std::max(dp[i - zeroNums[k]][j - oneNums[k]] + 1, dp[i][j]);
                }
            }
        }

        return dp[m][n];
    }
};

int main()
{
    std::vector<std::string> strs1 = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    Solution solution;
    std::cout << solution.findMaxForm(strs1, m, n) << std::endl;

    std::vector<std::string> strs2 = {"10", "0", "1"};
    m = 1, n = 1;
    std::cout << solution.findMaxForm(strs2, m, n) << std::endl;
    return 0;
}
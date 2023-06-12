#include <iostream>
#include <vector>

class Solution
{
public:
    bool canWin(std::string state)
    {
        int n = state.size();
        // dp[i][j]:先手翻转state[i:j]是否存在必胜的方法
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        for (int i = n - 2; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (i + 1 == j)
                {
                    dp[i][j] = (state[i] == '+') && (state[j] == '+');
                    continue;
                }
                for (int k = i; k < j && !dp[i][j]; ++k)
                {
                    if (state[k] == '+' && state[k + 1] == '+')
                    {
                        if (k == i)
                        {
                            dp[i][j] = !dp[k + 2][j];
                        }
                        else if (k == j - 1)
                        {
                            dp[i][j] = !dp[i][k - 1];
                        }
                        else
                        {
                            dp[i][j] = !(dp[i][k - 1] ^ (dp[k + 2][j]));
                        }
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
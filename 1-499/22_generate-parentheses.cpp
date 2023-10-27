#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        // dp[i]:i + 1对括号数的所有可能的组合
        std::vector<std::unordered_set<std::string>> dp(n);
        dp[0].insert("()");

        for (int i = 1; i < n; ++i)
        {
            for (auto it = dp[i - 1].begin(); it != dp[i - 1].end(); ++it)
            {
                dp[i].insert(*it + "()");
                dp[i].insert("()" + *it);
                for (int j = 0; j < it->size(); ++j)
                {
                    std::string s = it->substr(0, j) + "(" + it->substr(j, 1) + ")"
                                    + (j == it->size() - 1 ? "" : it->substr(j + 1));
                    dp[i].insert(s);
                }
            }
        }

        std::vector<std::string> ans(dp[n - 1].begin(), dp[n - 1].end());
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

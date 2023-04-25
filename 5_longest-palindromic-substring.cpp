#include <iostream>
#include <vector>

class Solution
{
public:
    std::string longestPalindrome(std::string s)
    {
        int size = s.size();
        // dp[i][j]:s[i:j]是回文子串
        std::vector<std::vector<bool>> dp(size, std::vector<bool>(size, false));

        int maxLength = 0;
        int index = 0;
        for (int i = size - 1; i >= 0; --i)
        {
            for (int j = i; j < size; ++j)
            {
                if (i == j)
                {
                    dp[i][j] = true;
                }
                else if (j - i == 1)
                {
                    dp[i][j] = (s[i] == s[j]);
                }
                else
                {
                    dp[i][j] = ((s[i] == s[j]) && dp[i + 1][j - 1]);
                }

                if (dp[i][j] && j - i + 1 > maxLength)
                {
                    maxLength = j - i + 1;
                    index = i;
                }
            }
        }

        return s.substr(index, maxLength);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
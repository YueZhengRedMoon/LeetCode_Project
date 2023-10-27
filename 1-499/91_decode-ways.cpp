#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int numDecodings(std::string s)
    {
        if (s[0] == '0') return 0;

        int len = s.size();
        std::unordered_set<std::string> message = {"1", "2", "3", "4", "5", "6", "7", "8", "9" , "10",
                                                   "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
                                                   "21", "22", "23", "24", "25", "26"};

        // dp[i]:s[0:i]可以解码出的总数
        std::vector<int> dp(len + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= len; ++i)
        {
            if (s[i - 1] != '0')
            {
                dp[i] = dp[i - 1];
            }

            std::string key({s[i - 2], s[i - 1]});
            if (message.find(key) != message.end())
            {
                dp[i] += dp[i - 2];
            }
        }

        return dp[len];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

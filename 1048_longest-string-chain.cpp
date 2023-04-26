#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int longestStrChain(std::vector<std::string> &words)
    {
        std::sort(words.begin(), words.end(),
                  [](const std::string &lhs, const std::string &rhs){return lhs.size() < rhs.size();});

        // dp[i]:以words[i]结尾的字符串链的最大长度
        std::vector<int> dp(words.size(), 1);

        int result = 1;
        for (int i = 1; i < words.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                int lengthDiff = words[i].size() - words[j].size();
                if (lengthDiff > 1)
                {
                    break;
                }
                if (lengthDiff == 1 && isSubSequence(words[j], words[i]))
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                    if (dp[i] > result)
                    {
                        result = dp[i];
                    }
                }
            }
        }

        return result;
    }

private:
    bool isSubSequence(const std::string &subSequence, const std::string & sequence)
    {
        int i = 0;
        for (auto& c : sequence)
        {
            if (c == subSequence[i])
            {
                ++i;
            }
            if (i == subSequence.size())
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
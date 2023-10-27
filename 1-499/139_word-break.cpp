#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    bool wordBreak(std::string s, std::vector<std::string> &wordDict)
    {
        // dp[j]:s[0:j - 1]是否可以由wordDict中的单词构成
        std::vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int j = 1; j <= s.size(); ++j)
        {
            for (int i = 0; i < wordDict.size(); ++i)
            {
                int index = j - wordDict[i].size();
                if (index >= 0 && dp[index])
                {
                    // s[0:index - 1] 可以由wordDict中的单词构成
                    // 检查s[index:j - 1]是否等于wordDict[i]
                    dp[j] = true;
                    for (int k1 = index, k2 = 0; k1 < j; ++k1, ++k2)
                    {
                        if (s[k1] != wordDict[i][k2])
                        {
                            dp[j] = false;
                            break;
                        }
                    }

                    if (dp[j])
                    {
                        break;
                    }
                }
            }
        }

        return dp[s.size()];
    }
};

class Solution2
{
public:
    bool wordBreak(std::string s, std::vector<std::string> &wordDict)
    {
        std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
        std::vector<bool> memory(s.size(), true);
        return backtracking(s, wordSet, memory, 0);
    }

private:
    bool backtracking(const std::string &s, const std::unordered_set<std::string> &wordSet,
                      std::vector<bool> &memory, int startIndex)
    {
        if (startIndex >= s.size())
            return true;

        if (!memory[startIndex])
            return memory[startIndex];

        for (int i = startIndex; i < s.size(); ++i)
        {
            std::string word = s.substr(startIndex, i - startIndex + 1);
            if (wordSet.find(word) != wordSet.end() && backtracking(s, wordSet, memory, i + 1))
                return true;
        }

        memory[startIndex] = false; // 记录以startIndex开始的子串不可以被拆分的
        return false;
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::string> wordDict = {"leet", "code"};
    std::string s("leetcode");
    std::cout << (solution.wordBreak(s, wordDict) ? "true" : "false") << std::endl;
    return 0;
}

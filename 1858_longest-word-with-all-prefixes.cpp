#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "debug.h"

class Solution
{
public:
    std::string longestWord(std::vector<std::string> &words)
    {
        std::sort(words.begin(), words.end(), [](const std::string &lhs, const std::string &rhs) {
            if (lhs.size() == rhs.size())
                return lhs < rhs;
            return lhs.size() < rhs.size();
        });

        int maxLen = 0;
        std::string *ansPtr = nullptr;
        // 满足所有前缀都在words中的字符串
        std::unordered_set<std::string> set;
        set.insert("");
        for (std::string &word : words)
        {
            int len = word.size();
            std::string prefix = word.substr(0, len - 1);
            if (set.find(prefix) != set.end())
            {
                set.insert(word);
                if (len > maxLen)
                {
                    maxLen = len;
                    ansPtr = &word;
                }
            }
        }

        return ansPtr == nullptr ? "" : *ansPtr;
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> words = {"k","ki","kir","kira","kiran"};
    std::string ans = solution.longestWord(words);
    logObj(ans);
    return 0;
}

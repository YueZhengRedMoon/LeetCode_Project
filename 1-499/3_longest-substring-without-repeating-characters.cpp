#include <iostream>
#include <unordered_map>

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        std::unordered_map<int, int> lastIndex;
        int maxLen = 0;
        int start = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (lastIndex.find(s[i]) == lastIndex.end())
            {
                lastIndex[s[i]] = i;
            }
            else
            {
                if (lastIndex[s[i]] >= start)
                {
                    start = lastIndex[s[i]] + 1;
                }
                lastIndex[s[i]] = i;
            }
            maxLen = std::max(maxLen, i - start + 1);
        }
        return maxLen;
    }
};

int main()
{
    Solution solution;
    std::string s = "aabaab!bb";
    int result = solution.lengthOfLongestSubstring(s);
    std::cout << result << std::endl;
    return 0;
}

#include <iostream>
#include <unordered_map>

class Solution
{
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k)
    {
        if (k == 0)
            return 0;

        std::unordered_map<char, int> lastIndex;
        int ans = 0, begin = 0, len = s.size();
        for (int i = 0; i < len; ++i)
        {
            auto it = lastIndex.find(s[i]);
            if (it != lastIndex.end())
            {
                it->second = i;
            }
            else
            {
                if (lastIndex.size() < k)
                {
                    lastIndex[s[i]] = i;
                }
                else
                {
                    int minIndex = len;
                    int minChar;
                    for (it = lastIndex.begin(); it != lastIndex.end(); ++it)
                    {
                        if (it->second < minIndex)
                        {
                            minChar = it->first;
                            minIndex = it->second;
                        }
                    }
                    begin = minIndex + 1;
                    lastIndex.erase(minChar);
                    lastIndex[s[i]] = i;
                }
            }
            ans = std::max(ans, i - begin + 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

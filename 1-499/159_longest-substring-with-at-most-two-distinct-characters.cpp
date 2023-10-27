#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int lengthOfLongestSubstringTwoDistinct(std::string s)
    {
        // 每种字符最后出现的索引
        std::unordered_map<char, int> indices;
        indices.reserve(2);
        int begin = 0, ans = 0, len = s.size();
        for (int i = 0; i < len; ++i)
        {
            auto mapIt = indices.find(s[i]);
            if (mapIt != indices.end())
            {
                mapIt->second = i;
            }
            else
            {
                if (indices.size() < 2)
                {
                    indices[s[i]] = i;
                }
                else
                {
                    auto it1 = indices.begin();
                    auto it2 = indices.begin();
                    ++it2;
                    if (it1->second < it2->second)
                    {
                        begin = it1->second + 1;
                        indices.erase(it1);
                        indices[s[i]] = i;
                    }
                    else
                    {
                        begin = it2->second + 1;
                        indices.erase(it2);
                        indices[s[i]] = i;
                    }
                }
            }
            ans = std::max(ans, i - begin + 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
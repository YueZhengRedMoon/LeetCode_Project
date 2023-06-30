#include <iostream>
#include <unordered_map>
#include <deque>

class Solution
{
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k)
    {
        std::deque<std::pair<char, int>> indices;
        std::unordered_map<char, std::deque<std::pair<char, int>>::iterator> IterMap;

        int len = s.size(), begin = 0;
        for (int i = 0; i < len; ++i)
        {
            auto mapIt = IterMap.find(s[i]);
            if (mapIt != IterMap.end())
            {
                mapIt->second->second = i;
            }
            else
            {
                if (indices.size() < k)
                {
                    indices.emplace_back(s[i], i);
                    auto it = indices.end() - 1;
                    IterMap[s[i]] = it;
                }
                else
                {
                    std::pair<char, int> front = indices.front();
                    begin = front.second + 1;
                    IterMap.erase(front.first);
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>

class Solution
{
public:
    std::vector<std::string> commonChars(std::vector<std::string> &words)
    {
        // first:出现在字符串中的次数
        // second:在每个字符串中最少出现的次数
        std::unordered_map<char, std::pair<int, int>> map;
        int multiSet[26];

        for (const auto& word : words)
        {
            std::memset(multiSet, 0, sizeof(multiSet));
            for (char c : word)
            {
                ++multiSet[c - 'a'];
            }
            for (int i = 0; i < 26; ++i)
            {
                if (multiSet[i] == 0)
                    continue;

                char c = 'a' + i;
                if (map.find(c) == map.end())
                {
                    map.insert({c, {1, multiSet[i]}});
                }
                else
                {
                    auto &element = map[c];
                    ++element.first;
                    if (element.second > multiSet[i])
                    {
                        element.second = multiSet[i];
                    }
                }
            }
        }

        std::vector<std::string> result;
        for (auto it = map.cbegin(); it != map.cend(); ++it)
        {
            if (it->second.first == words.size())
            {
                for (int i = 0; i < it->second.second; ++i)
                {
                    result.emplace_back(1, it->first);
                }
            }
        }

        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
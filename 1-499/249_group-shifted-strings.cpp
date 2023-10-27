#include <iostream>
#include <vector>
#include <unordered_map>
#include "../debug.h"

class Solution
{
public:
    std::vector<std::vector<std::string>> groupStrings(std::vector<std::string> &strings)
    {
        std::unordered_map<std::string, std::vector<std::string>> group;
        for (const std::string &s : strings)
        {
            group[shift(s)].emplace_back(s);
        }

        std::vector<std::vector<std::string>> ans;
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            ans.push_back(std::move(it->second));
        }
        return ans;
    }

private:
    // 移位s，使s的第一个字符变为'a'
    std::string shift(const std::string &s)
    {
        std::string res(s);
        int delta = s[0] - 'a', len = s.size();
        for (int i = 0; i < len; ++i)
        {
            res[i] = (s[i] - 'a' + 26 - delta) % 26 + 'a';
        }
        return res;
    }
};

int main()
{
    Solution solution;
    return 0;
}
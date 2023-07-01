#include <iostream>
#include <vector>
#include <map>

class Solution
{
public:
    std::vector<std::vector<std::string>> groupStrings(std::vector<std::string> &strings)
    {
        std::map<std::vector<int>, std::vector<std::string>> group;
        for (const std::string &s : strings)
        {
            group[getPattern(s)].emplace_back(s);
        }
        std::vector<std::vector<std::string>> ans;
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            ans.push_back(std::move(it->second));
        }
        return ans;
    }

private:
    std::vector<int> getPattern(const std::string &s)
    {
        int len = s.size();
        std::vector<int> pattern(len);
        pattern[0] = 0;
        for (int i = 1; i < len; ++i)
        {
            pattern[i] = s[i] - s[i - 1];
        }
        return pattern;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
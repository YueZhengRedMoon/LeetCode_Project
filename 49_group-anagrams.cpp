#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> group;

        for (const auto& str : strs)
        {
            std::string strCopy(str);
            std::sort(strCopy.begin(), strCopy.end());
            group[strCopy].push_back(str);
        }

        std::vector<std::vector<std::string>> ans;
        ans.reserve(group.size());
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            ans.push_back(std::move(it->second));
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

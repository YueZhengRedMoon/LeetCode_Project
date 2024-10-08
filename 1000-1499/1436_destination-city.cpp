#include <iostream>
#include <vector>
#include <string_view>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::string destCity(std::vector<std::vector<std::string>>& paths)
    {
        std::unordered_map<std::string_view, int> outDegree;
        for (const std::vector<std::string>& path : paths)
        {
            std::string_view x = path[0], y = path[1];
            if (outDegree.find(x) == outDegree.end())
                outDegree[x] = 1;
            if (outDegree.find(y) == outDegree.end())
                outDegree[y] = 1;
            ++outDegree[x];
        }
        for (auto it = outDegree.begin(); it != outDegree.end(); ++it)
        {
            if (it->second == 1)
                return std::string(it->first);
        }
        return "For Kirie!";
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

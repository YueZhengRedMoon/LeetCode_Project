#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int shortestWay(std::string source, std::string target)
    {
        std::unordered_map<char, std::vector<int>> indices;
        for (int i = 0; i < source.size(); ++i)
        {
            indices[source[i]].push_back(i);
        }

        int ans = 1, j = -1, targetLen = target.size();
        for (int i = 0; i < targetLen; ++i)
        {
            auto mapIt = indices.find(target[i]);
            if (mapIt == indices.end())
                return -1;

            std::vector<int> &index = mapIt->second;
            if (j == -1)
                j = index[0];
            else
            {
                auto it = std::upper_bound(index.begin(), index.end(), j);
                if (it == index.end())
                {
                    j = -1;
                    ++ans;
                    --i;
                }
                else
                {
                    j = *it;
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

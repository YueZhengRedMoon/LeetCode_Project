#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int longestCommonPrefix(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        std::unordered_set<int> prefixSet;
        std::unordered_set<int> visit1, visit2;
        for (int x : arr1)
        {
            if (visit1.find(x) != visit1.end())
            {
                continue;
            }
            visit1.insert(x);

            while (x)
            {
                prefixSet.insert(x);
                x /= 10;
            }
        }

        int maxPrefix = 0;
        for (int y : arr2)
        {
            if (visit2.find(y) != visit2.end())
            {
                continue;
            }
            visit2.insert(y);
            while (y)
            {
                if (prefixSet.find(y) != prefixSet.end())
                {
                    if (y > maxPrefix)
                        maxPrefix = y;
                    break;
                }
                y /= 10;
            }
        }
        return maxPrefix ? std::to_string(maxPrefix).length() : 0;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
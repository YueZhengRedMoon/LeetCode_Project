#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    bool uniqueOccurrences(std::vector<int> &arr)
    {
        std::unordered_map<int, int> frequency;
        for (int num : arr)
        {
            ++frequency[num];
        }

        std::unordered_set<int> set;
        for (auto it = frequency.begin(); it != frequency.end(); ++it)
        {
            auto result = set.insert(it->second);
            if (!result.second)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
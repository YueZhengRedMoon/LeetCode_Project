#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> successfulPairs(std::vector<int> &spells, std::vector<int> &potions, long long success)
    {
        int n = spells.size();
        std::vector<int> pairs(n);
        std::vector<long long> potionsCopy(potions.begin(), potions.end());
        std::sort(potionsCopy.begin(), potionsCopy.end());
        for (int i = 0; i < n; ++i)
        {
            pairs[i] = potionsCopy.end() - std::lower_bound(potionsCopy.begin(), potionsCopy.end(), (success + spells[i] - 1) / spells[i]);
        }
        return pairs;
    }
};

class Solution2
{
public:
    std::vector<int> successfulPairs(std::vector<int> &spells, std::vector<int> &potions, long long success)
    {
        std::sort(potions.begin(), potions.end());
        for (int &x : spells)
        {
            long long target = (success - 1) / x;
            if (target < potions.back())
            {
                x = potions.end() - std::upper_bound(potions.begin(), potions.end(), (int) target);
            }
            else
            {
                x = 0;
            }
        }
        return spells;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

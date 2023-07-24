#include <iostream>
#include <unordered_set>

class Solution
{
public:
    int numJewelsInStones(std::string jewels, std::string stones)
    {
        std::unordered_set<char> jewelsSet;
        for (char j : jewels)
        {
            jewelsSet.emplace(j);
        }
        int ans = 0;
        for (char s : stones)
        {
            if (jewelsSet.find(s) != jewelsSet.end())
            {
                ++ans;
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

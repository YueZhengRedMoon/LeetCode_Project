#include <iostream>
#include <vector>

class Solution
{
public:
    int minCount(std::vector<int> &coins)
    {
        int ans = 0;
        for (int coin : coins)
        {
            ans += coin / 2 + (coin % 2 == 0 ? 0 : 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

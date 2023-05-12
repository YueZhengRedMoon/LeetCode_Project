#include <iostream>
#include <vector>
#include <bitset>

class Solution
{
public:
    int findMaxK(std::vector<int> &nums)
    {
        std::bitset<2001> bitset;
        int ans = -1;
        for (int num : nums)
        {
            bitset.set(num + 1000);
            if (bitset.test(-num + 1000))
            {
                ans = std::max(ans, std::abs(num));
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
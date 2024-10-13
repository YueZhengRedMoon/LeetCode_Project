#include <iostream>
#include <vector>

class Solution
{
public:
    int duplicateNumbersXOR(std::vector<int>& nums)
    {
        int ans = 0;
        long long vis = 0;
        for (int x : nums)
        {
            if ((1ll << x) & vis) // x在vis中
            {
                ans ^= x;
            }
            else
            {
                vis |= 1ll << x;
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

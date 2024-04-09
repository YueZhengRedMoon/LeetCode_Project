#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumCount(std::vector<int>& nums)
    {
        auto it = std::lower_bound(nums.begin(), nums.end(), 0);
        int neg = it - nums.begin();

        it = std::upper_bound(nums.begin(), nums.end(), 0);
        int pos = nums.end() - it;

        return std::max(pos, neg);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

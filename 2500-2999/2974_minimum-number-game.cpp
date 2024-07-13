#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> numberGame(std::vector<int>& nums)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i += 2)
        {
            std::swap(nums[i], nums[i + 1]);
        }
        return nums;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

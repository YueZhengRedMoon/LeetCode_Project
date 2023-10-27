#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> sortArrayByParityII(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        int even = 0;   // 偶数索引
        int odd = 1;    // 奇数索引
        while (even < numsSize && odd < numsSize)
        {
            while (even < numsSize && nums[even] % 2 == 0)
                even += 2;

            while (odd < numsSize && nums[odd] % 2 == 1)
                odd += 2;

            if (even < numsSize && odd < numsSize)
                std::swap(nums[even], nums[odd]);
        }

        return nums;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

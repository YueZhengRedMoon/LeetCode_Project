#include <iostream>
#include <vector>

class Solution1
{
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int xorSum = 0;
        for (int x : nums)
        {
            xorSum ^= x;
        }
        return xorSum;
    }
};

class Solution2
{
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int n = nums.size();
        int left = 0, right = n;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (mid == 0 || mid == n - 1)
            {
                return nums[mid];
            }
            // 中间的数与左右两边的数都不同，它就是唯一出现一次的数
            else if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
            {
                return nums[mid];
            }
            // 当前位于奇数下标（在nums中的序号是偶数）
            else if ((mid % 2) == 1)
            {
                if (nums[mid] == nums[mid - 1])
                {
                    // 当前的数与左边的数相同，说明nums[0, mid]都是两两成对的，答案在右边
                    left = mid + 1;
                }
                else
                {
                    // 当前的数与左边的数不同，唯一出现一次的数在左边
                    right = mid;
                }
            }
            // 当前数位于偶数下标（在nums中的序号是奇数）
            else
            {
                if (nums[mid] == nums[mid - 1])
                {
                    // 当前的数与左边的数相同，说明唯一的数在左边
                    right = mid;
                }
                else
                {
                    // 当前的数与左边的数不同，说明nums[0, mid)中的数都是两两成对的，唯一的数在右边
                    left = mid + 1;
                }
            }
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

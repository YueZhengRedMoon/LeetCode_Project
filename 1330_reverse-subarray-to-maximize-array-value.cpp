#include <iostream>
#include <vector>

/** 枚举翻转的起始位置L和R
 *  假设翻转前的数组值为value1, 反转nums[L:R]后的数组值为value2，
 *  则有value2 = value1 - abs(nums[L]-nums[L-1]) - abs(nums[R+1] - nums[R])
 *                      + abs(nums[R]-nums[L-1]) + abs(nums[R+1]-nums[L])
 *  value1是定值，因此就是要最大化 x = - abs(nums[L]-nums[L-1]) - abs(nums[R+1] - nums[R])
 *                                 + abs(nums[R]-nums[L-1]) + abs(nums[R+1]-nums[L])
 *  假设nums[L], nums[L-1], nums[R], nums[R+1]四个值按从小到大排列是a, b, c, d
 *  则使abs(nums[L]-nums[L-1])结果为正的可能是:     d-c, d-b, d-a, c-b, c-a, b-a
 *  对应的使abs(nums[R+1]-nums[R])结果为正的可能是:  b-a, c-a, c-b, d-a, d-b, d-c
 *  当nums[L]-nums[L-1]=d-c，nums[R+1]-nums[R]=b-a时，x = -(d-c) - (b-a) + |a-c| + |b-d| = 2 * (c - b) >= 0
 *  当nums[L]-nums[L-1]=d-b，nums[R+1]-nums[R]=c-a时，x = -(d-b) - (c-a) + |a-b| + |c-d| = 2 * (b - c) <= 0
 *  当nums[L]-nums[L-1]=d-a，nums[R+1]-nums[R]=c-b时，x = -(d-a) - (c-b) + |b-a| + |c-d| = 2 * (b - c) <= 0
 *  当nums[L]-nums[L-1]=c-b，nums[R+1]-nums[R]=d-a时，x = -(c-b) - (d-a) + |a-b| + |d-c| = 2 * (b - c) <= 0
 *  当nums[L]-nums[L-1]=c-a，nums[R+1]-nums[R]=d-b时，x = -(c-a) - (d-b) + |b-a| + |d-c| = 2 * (b - d) <= 0
 *  当nums[L]-nums[L-1]=b-a，nums[R+1]-nums[R]=d-c时，x = -(b-a) - (d-c) + |c-a| + |d-b| = 2 * (c - b) >= 0
 *
 *  即当有nums[L-1]=c, nums[L] = d, nums[R]=a, nums[R+1]=b 或 nums[L-1]=a, nums[L] = b, nums[R]=c, nums[R+1]=d时才能是x最大
 *  即当两个相邻数对中一个数对中的较大值小于另一个数对的较小值时，求它们的差的2倍，再加上value1，即为value2 */
class Solution
{
public:
    int maxValueAfterReverse(std::vector<int> &nums)
    {

    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
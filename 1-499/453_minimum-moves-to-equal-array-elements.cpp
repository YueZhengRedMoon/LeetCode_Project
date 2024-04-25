#include <iostream>
#include <vector>

class Solution
{
public:
    int minMoves(std::vector<int>& nums)
    {
        // 每次操作等价于将一个数减一，目标是让数组中所有比最小元素大的元素减少为最小元素
        int n = nums.size();
        long long sum = 0, min = nums[0];
        for (int num : nums)
        {
            sum += num;
            if (num < min)
                min = num;
        }
        return (int) (sum - (min * n));
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

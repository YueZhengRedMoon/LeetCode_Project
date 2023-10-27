#include <iostream>
#include <vector>

class Solution
{
public:
    void wiggleSort(std::vector<int> &nums)
    {
        // 重新排序后的数组，偶数索引的数比奇数索引的数小
        int n = nums.size();
        for (int i = 0, j = 1; j < n; i += 2, j += 2)
        {
            if (nums[i] > nums[j])
            {
                std::swap(nums[i], nums[j]);    // nums[i] <= nums[j]
            }
            if (j + 1 < n && nums[j + 1] > nums[j])   // j + 1是偶数索引
            {
                // nums[j+1] > nums[j] -> nums[j+1] > nums[i]
                std::swap(nums[j], nums[j + 1]);
            }
            // nums[i] <= nums[j] >= nums[j+1],j为奇数
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

void printVector(const std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

class Solution
{
public:
    int largestSumAfterKNegations(std::vector<int> &nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        std::cout << "排序后：" << std::endl;
        printVector(nums);

        // 先将所有负数反转
        int i;
        for (i = 0; i < nums.size() && nums[i] < 0 && k > 0; ++i, --k)
        {
            nums[i] *= -1;
        }

        std::cout << "反转负数后：" << std::endl;
        printVector(nums);

        // 还需要反转
        if (k > 0)
        {
            // 遍历到了最后一个数，说明k > nums.size()，此时最小的数是反转前最大的数
            if (i == nums.size())
            {
                --i;
            }
            // 遍历到了正数
            else
            {
                // 找到此时最小的正数
                if (i > 0 && nums[i - 1] < nums[i])
                {
                    --i;
                }
            }
            if (k % 2 == 1)
            {
                std::cout << "反转" << nums[i] << std::endl;
                nums[i] *= -1;
            }
        }

        std::cout << "反转完成：" << std::endl;
        printVector(nums);
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        return sum;
    }
};

int main()
{
    // 6 -8 3 -5 -3 -5 -2 6
    std::vector<int> nums;
    int n, num, k;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        nums.push_back(num);
    }
    std::cin >> k;

    Solution solution;
    std::cout << solution.largestSumAfterKNegations(nums, k) << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumPairRemoval(std::vector<int>& nums)
    {
        int ans = 0, n = nums.size();
        bool isAsc;  // nums是否已经是非递减排序
        do
        {
            isAsc = true;
            int pIdx = 0;   // nums[pIdx-1],nums[pIdx]的和最小
            int minSum = INT_MAX;
            for (int i = 1; i < n; ++i)
            {
                if (nums[i] < nums[i - 1])
                {
                    isAsc = false;
                }
                if (nums[i] + nums[i - 1] < minSum)
                {
                    minSum = nums[i] + nums[i - 1];
                    pIdx = i;
                }
            }

            if (!isAsc)
            {
                // 将nums[pIdx-1]和nums[pIdx]替换为minSum
                nums[pIdx - 1] = minSum;
                --n;
                for (int i = pIdx; i < n; ++i)
                {
                    nums[i] = nums[i + 1];
                }
                ++ans;

                // 打印移除最小数对后的nums数组
                std::cout << '[';
                for (int i = 0; i < n - 1; ++i)
                {
                    std::cout << nums[i] << ", ";
                }
                std::cout << nums[n - 1] << ']' << std::endl;
            }
        } while (!isAsc);
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 3, 4};
    do
    {
        std::vector<int> numsCopy = nums;

        // 打印nums数组
        int n = numsCopy.size();
        std::cout << '[';
        for (int i = 0; i < n - 1; ++i)
        {
            std::cout << numsCopy[i] << ", ";
        }
        std::cout << numsCopy[n - 1] << ']' << std::endl;

        int ans = solution.minimumPairRemoval(numsCopy);
        std::cout << "ans = " << ans << '\n' << std::endl;
    } while (std::next_permutation(nums.begin(), nums.end()));
    return 0;
}
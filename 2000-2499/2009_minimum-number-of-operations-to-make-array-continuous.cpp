#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int m = std::unique(nums.begin(), nums.end()) - nums.begin();   // 将数组原地去重
        int ans = 0, left = 0;
        // 对于去重后数组中的每个元素x，如果其位置不变，则操作完成后连续数组的范围为[x-n+1, x]
        // 维护一个滑动窗口，统计滑动窗口内有多少个元素位置不需要改变
        for (int i = 0; i < m; ++i)
        {
            while (nums[left] < nums[i] - n + 1)    // nums[left]不在窗口内
                ++left;
            ans = std::max(ans, i - left + 1);  // 滑动窗口内最多有多少个点固定不同
        }
        return n - ans;
    }
};

namespace Error
{
    class Solution
    {
    public:
        int minOperations(std::vector<int>& nums)
        {
            std::sort(nums.begin(), nums.end());
            int n = nums.size();    // nums的原始元素数量
            int m = std::unique(nums.begin(), nums.end()) - nums.begin();   // 去重后数组元素的数量
            nums.resize(m);
            int ans = m + 1;
            for (int num : nums)
            {
                int left = 0, right = ans;
                if (left >= right)
                    break;
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    if (check(nums, num, mid))  // 可以通过mid次变换将nums变为最小值为num的连续数组
                    {
                        ans = mid;
                        right = mid;
                    }
                    else
                    {
                        left = mid + 1;
                    }
                }
            }
            return ans + n - m; // 重复的n-m个元素一定会被替换
        }

    private:
        // 检查升序数组nums是否可以通过replaceCount次替换将其变为最小值为minNum的连续数组
        bool check(std::vector<int>& nums, int minNum, int replaceCount)
        {
            int n = nums.size(), needReplace = 0;

            // 通过二分查找，找到最后一个小于minNum的数
            auto it = std::lower_bound(nums.begin(), nums.end(), minNum);
            if (it != nums.begin())
            {
                needReplace = it - nums.begin() - 1;
            }

            // 通过二分查找，找到第一个大于等于maxNum = minNum + n的数
            needReplace += nums.end() - std::lower_bound(nums.begin(), nums.end(), minNum + n);

            return needReplace <= replaceCount;
        }
    };
}

int main()
{
    Error::Solution solution;
    std::vector<int> nums = {41,33,29,33,35,26,47,24,18,28};
    int ans = solution.minOperations(nums);
    std::cout << ans << std::endl;
    return 0;
}

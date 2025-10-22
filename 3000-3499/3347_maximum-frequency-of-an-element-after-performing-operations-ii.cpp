#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations)
    {
        std::sort(nums.begin(), nums.end());

        int n = nums.size(), ans = 0, cnt = 0, left = 0, right = 0;

        // 同向三指针
        for (int i = 0; i < n; ++i)
        {
            // 计算元素值在 [x−k,x+k] 中的元素个数，这些元素都可以变成 x
            int x = nums[i];
            ++cnt;

            // 循环直到连续相同段的末尾，这样可以统计出 x 的出现次数
            if (i < n - 1 && x == nums[i + 1])
                continue;

            while (nums[left] < x - k)
                ++left;
            while (right < n && nums[right] <= x + k)
                ++right;

            // right-left: [x-k, x+k]中的所有元素的都可以在不超过numOperations次操作后变成x
            // cnt + numOperations: [x-k, x+k]中的元素数量太多了，之多只能进行numOperations次操作，加上本来就是x的cnt个数
            ans = std::max(ans, std::min(right - left, cnt + numOperations));

            cnt = 0;    // 枚举下一个x，重置cnt
        }

        if (ans >= numOperations)
            return ans;

        // 同向双指针，假设nums[left, right]中变成的数y不在nums中，则至多会有numOperations个数变成y
        for (left = 0, right = 0; right < n; ++right)
        {
            int x = nums[right];
            while (nums[left] < x - k * 2)
                ++left;

            ans = std::max(ans, right - left + 1);
        }
        return std::min(ans, numOperations);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
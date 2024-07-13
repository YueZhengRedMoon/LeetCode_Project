#include <iostream>
#include <vector>

class Solution
{
public:
    bool canSortArray(std::vector<int>& nums)
    {
        int n = nums.size(), lastOneCnt = -1, lastMax = -1, curMax = -1;
        for (int i = 0; i < n; ++i)
        {
            int curOneCnt = countOne(nums[i]);
            if (curOneCnt == lastOneCnt)
            {
                curMax = std::max(curMax, nums[i]);
            }
            else
            {
                lastMax = curMax;
                curMax = nums[i];
            }
            if (lastMax > nums[i])
                return false;
            lastOneCnt = curOneCnt;
        }
        return true;
    }

private:
    // 统计num的二进制表示中1的个数
    int countOne(int num)
    {
        int cnt = 0;
        while (num > 0)
        {
            num &= num - 1;
            ++cnt;
        }
        return cnt;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {3,16,8,4,2};
    bool ans = solution.canSortArray(nums);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}

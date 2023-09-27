#include <iostream>
#include <vector>

class Solution
{
public:
    // 定义cnt[i]表示nums数组中小于等于i的数
    // 假设重复的数是target，那么[1, target-1]里的所有数满足cnt[i] <= i, [target, n]里的所有数满足cnt[i] > i，具有单调性
    // 第一个满足cnt[i] > i的i即为target

    int findDuplicate(std::vector<int> &nums)
    {
        int n = nums.size(), left = 1, right = n, ans = -1;
        while (left < right)
        {
            int mid = (left + right) / 2, cnt = 0;
            for (int num : nums)
                cnt += (num <= mid);
            if (cnt > mid)
            {
                ans = mid;
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    // 将所有数二进制展开来考虑如何找出重复的数，如果能确定重复数每一位是1还是0就可以按位还原出重复的数
    // 考虑第i位，记:
    //  - nums数组中二进制展开后第i位为1的数有x个
    //  - 数字[1, n]这n个数二进制展开后第i位为1的数有y个
    // 则重复的数第i位为1当且仅当x > y

    int findDuplicate(std::vector<int> &nums)
    {
        int n = nums.size(), ans = 0, bitMax = 31;
        while (!(n - 1) >> bitMax)
            --bitMax;
        for (int bit = 0; bit <= bitMax; ++bit)
        {
            int x = 0, y = 0;
            for (int i = 0; i < n; ++i)
            {
                if (nums[i] & (1 << bit))
                    ++x;
                if (i >= 1 && (i & (1 << bit)))
                    ++y;
            }
            if (x > y)
                ans |= 1 << bit;
        }
        return ans;
    }
};

class Solution3
{
public:
    int findDuplicate(std::vector<int> &nums)
    {
        int slow = 0, fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

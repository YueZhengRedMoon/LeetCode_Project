#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int findFinalValue(std::vector<int>& nums, int original)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        while (set.find(original) != set.end())
        {
            original <<= 1;
        }
        return original;
    }
};

class Solution2
{
public:
    int findFinalValue(std::vector<int>& nums, int original)
    {
        std::unordered_set<int> set;
        for (int x : nums)
        {
            // 如果x = original * 2^k，则：
            //  - x是original的倍数
            // x / original是2的幂

            int k = x / original;
            if (x % original == 0 && (k & (k - 1)) == 0)    // k&(k-1)会将k最低位的1变为0，如果k&(k-1) == 0，则说明k是2的幂
            {
                set.insert(x);
            }
        }

        while (set.find(original) != set.end())
        {
            original <<= 1;
        }
        return original;
    }
};

class Solution3
{
public:
    int findFinalValue(std::vector<int>& nums, int original)
    {
        int mask = 0;
        for (int x : nums)
        {
            int k = x / original;
            if (x % original == 0 && (k & (k - 1)) == 0)
            {
                mask |= k;
            }
        }

        // 找最低位的0，等价于取反后，找最低位的1
        mask = ~mask;
        return original * (mask & -mask);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
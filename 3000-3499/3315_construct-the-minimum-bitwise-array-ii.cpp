#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> minBitwiseArray(std::vector<int>& nums)
    {
        // 如果nums[i]不为2，那么将nums[i]最低位的0右边的1变为0，即为答案

        int n = nums.size();
        std::vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i)
        {
            int x = nums[i];
            if (x != 2)
            {
                for (int j = 1; ; ++j)
                {
                    if (((1 << j) & x) == 0)
                    {
                        ans[i] = x & (~(1 << (j - 1)));
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
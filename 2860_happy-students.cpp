#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    // 未被选中的人其nums[i]应该尽可能大，被选中的人其nums[i]应该尽可能小

    int countWays(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());

        int ans = (nums[0] > 0), n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            int select = i + 1;
            if (select > nums[i] && (i == n - 1 || select < nums[i + 1]))
            {
                ++ans;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

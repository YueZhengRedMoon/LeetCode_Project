#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> divideArray(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans(n / 3, std::vector<int>(3));

        int first = -1; // 子数组中的第一个（最小）元素的值
        for (int i = 0; i < n; ++i)
        {
            if (first == -1)
            {
                first = nums[i];
            }
            else if (i % 3 == 2)
            {
                if (nums[i] - first > k)
                {
                    return {{}};
                }
                else
                {
                    first = -1;
                }
            }
            ans[i / 3][i % 3] = nums[i];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

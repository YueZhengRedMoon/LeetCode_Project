#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int matrixSum(std::vector<std::vector<int>> &nums)
    {
        int m = nums.size(), n = nums[0].size();
        for (int i = 0; i < m; ++i)
        {
            std::sort(nums[i].begin(), nums[i].end(), std::greater<int>());
        }

        int ans = 0;
        for (int j = 0; j < n; ++j)
        {
            int max = nums[0][j];
            for (int i = 1; i < m; ++i)
            {
                if (nums[i][j] > max)
                    max = nums[i][j];
            }
            ans += max;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>

class Solution
{
public:
    bool isZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        int n = nums.size();

        // 初始化差分数组
        std::vector<int> diff(n + 1);
        diff[0] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            diff[i] = nums[i] - nums[i - 1];
        }

        for (int i = 0; i < queries.size(); ++i)
        {
            int l = queries[i][0], r = queries[i][1];

            // 将区间[l, r]中的所有元素都减 1
            --diff[l];
            ++diff[r + 1];
        }

        int sumD = 0;
        for (int i = 0; i < n; ++i)
        {
            sumD += diff[i];
            if (sumD > 0)
                return false;
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

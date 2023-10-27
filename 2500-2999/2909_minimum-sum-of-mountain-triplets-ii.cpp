#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int minimumSum(std::vector<int> &nums)
    {
        const int inf = std::numeric_limits<int>::max();
        int n = nums.size();
        std::vector<int> rightMin(n);   // rightMin[i]:nums[i:n-1]中的最小值
        rightMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            rightMin[i] = std::min(nums[i], rightMin[i + 1]);
        }

        int leftMin = nums[0], ans = inf;
        for (int i = 1; i < n - 1; ++i)
        {
            if (leftMin < nums[i] && nums[i] > rightMin[i + 1])
            {
                ans = std::min(ans, leftMin + nums[i] + rightMin[i + 1]);
            }
            if (nums[i] < leftMin)
                leftMin = nums[i];
        }

        return ans == inf ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
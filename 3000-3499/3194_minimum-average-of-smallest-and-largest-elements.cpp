#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    double minimumAverage(std::vector<int>& nums)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        double ans = INT_MAX;
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            ans = std::min(ans, (nums[i] + nums[j]) / 2.0);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

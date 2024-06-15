#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumBeauty(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::pair<int, int>> ranges(n);
        for (int i = 0; i < n; ++i)
        {
            ranges[i].first = nums[i] - k;
            ranges[i].second = nums[i] + k;
        }

        int ans = 1;
        for (int i = 0, j = 1; j < n; ++j)
        {
            while (ranges[i].second < ranges[j].first)
                ++i;
            ans = std::max(ans, j - i + 1);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

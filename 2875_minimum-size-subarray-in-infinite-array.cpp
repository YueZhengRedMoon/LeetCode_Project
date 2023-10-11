#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

class Solution
{
public:
    int minSizeSubarray(std::vector<int> &nums, int target)
    {
        const long long inf = std::numeric_limits<long long>::max();
        long long total =  std::accumulate(nums.begin(), nums.end(), 0ll);
        int n = nums.size();
        long long targetModTotal = target % total;
        long long sum = 0, ans = inf;
        for (int left = 0, right = 0; right < n * 2; ++right)
        {
            sum += nums[right % n];
            while (sum > targetModTotal)
            {
                sum -= nums[left % n];
                ++left;
            }
            if (sum == targetModTotal)
            {
                ans = std::min(ans, right - left + 1ll);
            }
        }
        return ans == inf ? -1 : ans + (target / total) * n;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    long long minCost(std::vector<int> &nums, int x)
    {
        int n = nums.size();
        long long ans = std::accumulate(nums.begin(), nums.end(), 0ll);
        std::vector<int> minCost(nums); // minCost[j]:在操作i次后，巧克力j的最小成本
        for (int i = 1; i < n; ++i)
        {
            long long cost = (long long) x * i;
            for (int j = 0; j < n; ++j)
            {
                minCost[j] = std::min(minCost[j], nums[(j + i) % n]);
                cost += minCost[j];
            }
            if (cost < ans)
                ans = cost;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

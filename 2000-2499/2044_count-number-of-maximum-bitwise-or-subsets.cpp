#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

class Solution
{
public:
    int countMaxOrSubsets(std::vector<int>& nums)
    {
        // int maxOrSum = std::accumulate(nums.begin(), nums.end(), 0, std::bit_or<int>());
        int maxOrSum = std::accumulate(nums.begin(), nums.end(), 0, [](int a, int b) {return a | b;});
        int ans = 0;

        std::function<void(int, int)> dfs = [&](int i, int orSum) {
            if (i == nums.size())
            {
                if (orSum == maxOrSum)
                    ++ans;
                return;
            }

            dfs(i + 1, orSum | nums[i]);
            dfs(i + 1, orSum);
        };
        dfs(0, 0);

        return ans;
    }
};

class Solution2
{
public:
    int countMaxOrSubsets(std::vector<int>& nums)
    {
        int maxOrSum = std::accumulate(nums.begin(), nums.end(), 0, std::bit_or<int>());
        int ans = 0;
        int n = nums.size();

        std::function<void(int, int)> dfs = [&](int i, int orSum) {
            if (orSum == maxOrSum)  // 当前子集的按位或和已经等于maxOrSum
            {
                // orSum不可能再变大，剩下的下标在[i, n-1]中的每个数无论选还是不选，对应子集OR值都等于maxOrSum，一共有2^(n-i)种方案
                ans += 1 << (n - i);
                return;
            }

            if (i == n)
            {
                return;
            }

            dfs(i + 1, orSum | nums[i]);
            dfs(i + 1, orSum);
        };
        dfs(0, 0);

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

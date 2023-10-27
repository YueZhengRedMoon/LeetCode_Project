#include <iostream>
#include <vector>

class Solution
{
public:
    int subarraysWithMoreZerosThanOnes(std::vector<int> &nums)
    {
        int n = nums.size(), ans = 0, mod = 1e9 + 7;
        std::vector<int> cnts(2 * n + 1, 0);
        cnts[n] = 1;
        for (int i = 0, s = n, cnt = 0; i < n; ++i)
        {
            if (nums[i] == 1)
            {
                ++s;
                cnt += cnts[s];
            }
            else
            {
                --s;
                cnt -= cnts[s];
            }
            ++cnts[s];
            ans = (ans + cnt >= mod) ? (ans + cnt - mod) : ans + cnt;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums{0,1,1,0,1};
    int ans = solution.subarraysWithMoreZerosThanOnes(nums);
    std::cout << ans << std::endl;
    return 0;
}

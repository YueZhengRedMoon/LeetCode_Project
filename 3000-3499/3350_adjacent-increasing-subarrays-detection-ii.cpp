#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxIncreasingSubarrays(std::vector<int>& nums)
    {
        int ans = 0, cnt = 1, preCnt = 0, n = nums.size();
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] > nums[i - 1])
            {
                ++cnt;
            }
            else
            {
                preCnt = cnt;
                cnt = 1;
            }
            ans = std::max({ans, std::min(preCnt, cnt), cnt / 2});
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool hasIncreasingSubarrays(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        int cnt = 1;    // 当前位置严格递增的子数组的长度
        int preCnt = 0; // 上一个严格递增的子数组的长度
        int ans = 0;    // 最大的满足要求的值

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

        return ans >= k;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
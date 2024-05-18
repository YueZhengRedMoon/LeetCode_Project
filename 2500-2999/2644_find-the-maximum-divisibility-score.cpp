#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxDivScore(std::vector<int>& nums, std::vector<int>& divisors)
    {
        std::sort(nums.rbegin(), nums.rend());  // 从大到小排序
        std::sort(divisors.begin(), divisors.end());
        int maxCnt = -1, ans = 0;
        for (int d : divisors)
        {
            int cnt = 0;
            for (int i = 0; i < nums.size() && nums[i] >= d; ++i)
            {
                cnt += (nums[i] % d == 0);
            }
            if (cnt > maxCnt || (maxCnt == cnt && d < ans))
            {
                maxCnt = cnt;
                ans = d;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

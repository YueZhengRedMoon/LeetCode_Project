#include <iostream>
#include <vector>

class Solution
{
public:
    long long countSubarrays(std::vector<int>& nums, int minK, int maxK)
    {
        long long ans = 0;
        int n = nums.size();
        int minI = -1;  // minK最近出现的位置
        int maxI = -1;  // maxK最近出现的位置
        int i0 = -1;    // 在[minK, maxK]范围之外的最近元素位置

        for (int i = 0; i < n; ++i)
        {
            int x = nums[i];
            if (x == minK)
            {
                minI = i;
            }
            if (x == maxK)
            {
                maxI = i;
            }
            if (x < minK || x > maxK)
            {
                i0 = i;
            }
            ans += std::max(std::min(minI, maxI) - i0, 0);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

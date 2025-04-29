#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long countSubarrays(std::vector<int>& nums, int k)
    {
        int max = *std::max_element(nums.begin(), nums.end());
        long long ans = 0;
        for (int l = 0, r = 0, cnt = 0; r < nums.size(); ++r)
        {
            if (nums[r] == max)
            {
                ++cnt;
            }

            while (cnt == k)
            {
                if (nums[l] == max)
                {
                    --cnt;
                }
                ++l;
            }
            ans += l;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

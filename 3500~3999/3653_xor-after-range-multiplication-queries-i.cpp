#include <iostream>
#include <vector>

class Solution
{
public:
    int xorAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        int n = nums.size();
        for (const std::vector<int>& q : queries)
        {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            for (int i = l; l <= r; l += k)
            {
                nums[i] = (int) ((nums[i] * (long long) v) % 1'000'000'007);
            }
        }
        int ans = 0;
        for (int x : nums)
        {
            ans ^= x;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
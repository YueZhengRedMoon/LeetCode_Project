#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<bool> prefixesDivBy5(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<bool> ans(n, false);
        int x = 0;
        for (int i = 0; i < n; ++i)
        {
            x = ((x << 1) + nums[i]) % 5;
            if (x == 0)
                ans[i] = true;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
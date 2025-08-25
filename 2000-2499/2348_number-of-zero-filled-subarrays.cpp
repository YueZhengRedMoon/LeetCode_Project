#include <iostream>
#include <vector>

class Solution
{
public:
    long long zeroFilledSubarray(std::vector<int>& nums)
    {
        int n = nums.size();
        int i = 0;
        long long ans = 0;
        while (i < n)
        {
            if (nums[i] != 0)
            {
                ++i;
                continue;
            }

            int j = i + 1;
            while (j < n && nums[j] == 0)
                ++j;
            long long m = j - i;
            ans += (1 + m) * m / 2;
            i = j;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

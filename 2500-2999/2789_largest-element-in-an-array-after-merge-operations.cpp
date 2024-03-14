#include <iostream>
#include <vector>
#include <deque>

class Solution
{
public:
    long long maxArrayValue(std::vector<int>& nums)
    {
        int n = nums.size();
        long long sum = 0, ans = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            if (sum >= nums[i])
            {
                sum += nums[i];
            }
            else
            {
                ans = std::max(ans, sum);
                sum = nums[i];
            }
        }
        return std::max(ans, sum);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

class Solution
{
public:
    int maxRotateFunction(std::vector<int> &nums)
    {
        int f = 0, sum = 0, n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            f += i * nums[i];
            sum += nums[i];
        }
        int ans = f;
        for (int i = 1; i < n; ++i)
        {
            f += sum - n * nums[n - i];
            if (f > ans) ans = f;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

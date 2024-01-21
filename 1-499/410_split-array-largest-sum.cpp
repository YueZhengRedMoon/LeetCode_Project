#include <iostream>
#include <vector>

class Solution
{
public:
    int splitArray(std::vector<int> &nums, int k)
    {
        int max = 0, sum = 0;
        for (int num : nums)
        {
            sum += num;
            if (num > max)
                max = num;
        }

        // 检查nums数组是否可以划分为至多k个和至多为max的子数组
        auto check = [&nums, k](int maxSum) -> bool {
            int cnt = 1, sum = 0;
            for (int num : nums)
            {
                if (sum + num <= maxSum)
                {
                    sum += num;
                }
                else
                {
                    if (cnt++ == k)
                        return false;
                    sum = num;
                }
            }
            return true;
        };

        int lower = std::max(max - 1, (sum - 1) / k), upper = sum;
        while (lower + 1 < upper)
        {
            int mid = lower + (upper - lower) / 2;
            if (check(mid))
            {
                upper = mid;
            }
            else
            {
                lower = mid;
            }
        }

        return upper;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

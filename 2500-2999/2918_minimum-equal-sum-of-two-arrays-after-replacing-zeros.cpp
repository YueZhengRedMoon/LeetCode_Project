#include <iostream>
#include <vector>

class Solution
{
public:
    long long minSum(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        long long ans;
        auto [sum1, zeroCnt1] = calcSumAndCountZero(nums1);
        auto [sum2, zeroCnt2] = calcSumAndCountZero(nums2);
        sum1 += zeroCnt1;
        sum2 += zeroCnt2;
        if (sum1 > sum2)
        {
            if (zeroCnt2)
                ans = sum1;
            else
                ans = -1;
        }
        else if (sum1 < sum2)
        {
            if (zeroCnt1)
                ans = sum2;
            else
                ans = -1;
        }
        else
        {
            ans = sum1;
        }
        return ans;
    }

private:
    std::pair<long long, int> calcSumAndCountZero(const std::vector<int> &nums)
    {
        long long sum = 0;
        int zeroCnt = 0;
        for (int num : nums)
        {
            if (num == 0)
                ++zeroCnt;
            else
                sum += num;
        }
        return {sum, zeroCnt};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

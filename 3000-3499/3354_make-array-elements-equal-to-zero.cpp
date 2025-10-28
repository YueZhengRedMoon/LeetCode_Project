#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int countValidSelections(std::vector<int>& nums)
    {
        int ans = 0, leftSum = 0, rightSum = std::accumulate(nums.begin(), nums.end(), 0);
        for (int x : nums)
        {
            if (x == 0)
            {
                if (leftSum == rightSum)
                    ans += 2;
                else if (std::abs(leftSum - rightSum) == 1)
                    ++ans;
            }
            leftSum += x;
            rightSum -= x;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
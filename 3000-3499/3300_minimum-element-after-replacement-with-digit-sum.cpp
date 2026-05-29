#include <iostream>
#include <vector>

class Solution
{
public:
    int minElement(std::vector<int>& nums)
    {
        int ans = INT_MAX;
        for (int x : nums)
        {
            int digitSum = 0;
            while (x)
            {
                digitSum += x % 10;
                x /= 10;
            }
            if (digitSum < ans)
                ans = digitSum;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
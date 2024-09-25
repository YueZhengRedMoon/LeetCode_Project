#include <iostream>
#include <vector>

class Solution
{
public:
    int differenceOfSum(std::vector<int>& nums)
    {
        int elemSum = 0, digitSum = 0;
        for (int x : nums)
        {
            elemSum += x;
            while (x)
            {
                digitSum += x % 10;
                x /= 10;
            }
        }
        return std::abs(elemSum - digitSum);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

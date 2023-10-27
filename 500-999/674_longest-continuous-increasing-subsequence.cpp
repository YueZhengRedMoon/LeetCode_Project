#include <iostream>
#include <vector>

class Solution
{
public:
    int findLengthOfLCIS(std::vector<int> &nums)
    {
        int longestLength = 1;
        int currentLength = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > nums[i - 1])
            {
                ++currentLength;
            }
            else
            {
                if (currentLength > longestLength)
                {
                    longestLength = currentLength;
                }
                currentLength = 1;
            }
        }
        if (currentLength > longestLength)
        {
            longestLength = currentLength;
        }
        return longestLength;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
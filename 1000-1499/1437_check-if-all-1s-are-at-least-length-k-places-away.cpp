#include <iostream>
#include <vector>

class Solution
{
public:
    bool kLengthApart(std::vector<int>& nums, int k)
    {
        int last1Idx = -k - 1;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] == 1)
            {
                if (i - last1Idx - 1 < k)
                {
                    return false;
                }
                last1Idx = i;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
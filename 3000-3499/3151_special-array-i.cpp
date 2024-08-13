#include <iostream>
#include <vector>

class Solution
{
public:
    bool isArraySpecial(std::vector<int>& nums)
    {
        int flag = nums[0] % 2;
        for (int i = 1; i < nums.size(); ++i)
        {
            int newFlag = nums[i] % 2;
            if (newFlag == flag)
                return false;
            flag = newFlag;
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

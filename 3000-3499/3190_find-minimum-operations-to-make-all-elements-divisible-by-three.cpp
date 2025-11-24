#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumOperations(std::vector<int>& nums)
    {
        int ans = 0;
        for (int x : nums)
        {
            if (x % 3 != 0)
            {
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
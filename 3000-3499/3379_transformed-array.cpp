#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> constructTransformedArray(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i)
        {
            result[i] = nums[(((i + nums[i]) % n) + n) % n];
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
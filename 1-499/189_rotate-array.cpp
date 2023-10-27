#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    void rotate(std::vector<int> &nums, int k)
    {
        int size = nums.size();
        k %= size;
        std::reverse(nums.begin(), nums.begin() + size - k);
        std::reverse(nums.begin() + size - k, nums.end());
        std::reverse(nums.begin(), nums.end());
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
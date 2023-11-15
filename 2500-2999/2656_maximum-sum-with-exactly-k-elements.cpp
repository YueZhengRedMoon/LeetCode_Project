#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximizeSum(std::vector<int> &nums, int k)
    {
        int maxNum = *std::max_element(nums.begin(), nums.end());
        // maxNum + (maxNum + 1) + (maxNum + 2) + ... + (maxNum + k - 1)
        return k * maxNum + (k - 1) * k / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

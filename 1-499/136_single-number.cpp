#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        return std::accumulate(nums.begin(), nums.end(), 0, [](int a, int b) {return a ^ b;});
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

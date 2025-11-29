#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return sum - (sum / k) * k;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
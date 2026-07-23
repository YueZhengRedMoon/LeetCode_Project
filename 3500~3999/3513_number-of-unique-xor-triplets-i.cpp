#include <iostream>
#include <vector>

class Solution
{
public:
    int uniqueXorTriplets(std::vector<int>& nums)
    {
        size_t n = nums.size();
        return n <= 2 ? n : 1 << (32 - __builtin_clz(n));
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
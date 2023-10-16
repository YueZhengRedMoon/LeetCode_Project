#include <iostream>
#include <vector>
#include <tuple>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        int ans = 0;
        for (int i = 0; i < 32; ++i)
        {
            int total = 0;
            for (int num : nums)
            {
                total += ((num >> i) & 1);
            }
            if (total % 3)
            {
                ans |= (1 << i);
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        int a = 0, b = 0;
        for (int x : nums)
        {
            std::tie(a, b) = std::pair{(~a & b & x) | (a & ~b & ~x), ~a & (b ^ x)};
        }
        return b;
    }
};

class Solution3
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        int a = 0, b = 0;
        for (int x : nums)
        {
            b = ~a & (b ^ x);
            a = ~b & (a ^ x);
        }
        return b;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

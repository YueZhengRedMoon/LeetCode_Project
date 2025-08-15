#include <iostream>
#include <vector>

class Solution
{
public:
    bool isPowerOfFour(int n)
    {
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) > 0;
    }
};

class Solution2
{
public:
    bool isPowerOfFour(int n)
    {
        return n > 0 && (n & (n - 1)) == 0 && n % 3 == 1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

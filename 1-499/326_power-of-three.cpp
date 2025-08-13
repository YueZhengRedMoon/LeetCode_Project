#include <iostream>
#include <climits>

class Solution
{
public:
    bool isPowerOfThree(int n)
    {
        return n > 0 && 1162261467 % n == 0;
    }
};

int main()
{
    long long i = 1, x = 3;
    while (x <= INT_MAX)
    {
        x *= 3;
        ++i;
    }
    std::cout << "3^" << i - 1 << " = " << x / 3 << std::endl;
    return 0;
}

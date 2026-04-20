#include <iostream>

class Solution
{
public:
    int mirrorDistance(int n)
    {
        return std::abs(n - reverse(n));
    }

private:
    int reverse(int n)
    {
        int res = 0;
        while (n)
        {
            res = res * 10 + n % 10;
            n /= 10;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
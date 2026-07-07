#include <iostream>
#include <vector>

class Solution
{
public:
    long long sumAndMultiply(int n)
    {
        int x = 0, sum = 0, i = 1;
        while (n)
        {
            int d = n % 10;
            if (d)
            {
                x = d * i + x;
                sum += d;
                i *= 10;
            }
            n /= 10;
        }
        return (long long) x * sum;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
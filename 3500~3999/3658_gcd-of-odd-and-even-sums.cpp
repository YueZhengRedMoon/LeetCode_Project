#include <iostream>
#include <numeric>

class Solution
{
public:
    int gcdOfOddEvenSums(int n)
    {
        int maxOdd = 2 * (n - 1) + 1, maxEven = 2 * n;
        int sumOdd = (1 + maxOdd) * n / 2;
        int sumEven = (2 + maxEven) * n / 2;
        return std::gcd(sumOdd, sumEven);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
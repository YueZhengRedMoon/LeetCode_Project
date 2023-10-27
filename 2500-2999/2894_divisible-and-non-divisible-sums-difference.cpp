#include <iostream>
#include <vector>

class Solution
{
public:
    int differenceOfSums(int n, int m)
    {
        return nonDivisible(n, m) - divisible(n, m);
    }

private:
    // [1, n]中能被m的整除的整数之和
    int divisible(int n, int m)
    {
        int k = n / m;  // [1, n]中有k=n/m个整数能被m整除，即k, 2k, ... , mk
        return (1 + k) * k * m / 2;
    }

    // [1, n]中不能被m的整除的整数之和
    int nonDivisible(int n, int m)
    {
        return (1 + n) * n / 2 - divisible(n, m);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

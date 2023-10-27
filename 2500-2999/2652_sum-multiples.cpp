#include <iostream>
#include <vector>

class Solution
{
public:
    int sumOfMultiples(int n)
    {
        int sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
                sum += i;
        }
        return sum;
    }
};

class Solution2
{
public:
    int sumOfMultiples(int n)
    {
        return s(n, 3) + s(n, 5) + s(n, 7) - s(n, 15) - s(n, 21) - s(n, 35) + s(n, 105);
    }

private:
    // [1, n]中所有可以整除m的数的和
    int s(int n, int m)
    {
        int k = n / m;  // 在[1, n]中，m的倍数有k = n / m 个
        return k * (k + 1) * m / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>

class Solution
{
public:
    int smallestNumber(int n)
    {
        int x[10] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
        for (int i = 0; i < 10; ++i)
        {
            if (x[i] >= n)
                return x[i];
        }
        return -1;
    }
};

class Solution2
{
public:
    int smallestNumber(int n)
    {
        int m = 32 - __builtin_clz(n);  // m = n的二进制长度
        return (1 << m) - 1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
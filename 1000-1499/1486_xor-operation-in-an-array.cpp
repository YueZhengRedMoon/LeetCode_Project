#include <iostream>
#include <vector>

class Solution
{
public:
    int xorOperation(int n, int start)
    {
        int a = start / 2;
        int b = n & start & 1;
        return (xorN(a + n - 1) ^ xorN(a - 1)) * 2 + b;
    }

private:
    int xorN(int n)
    {
        switch (n % 4)
        {
            case 0: return n;
            case 1: return 1;
            case 2: return n + 1;
            default: return 0;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

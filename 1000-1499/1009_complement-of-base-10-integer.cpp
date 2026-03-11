#include <iostream>
#include <vector>

class Solution
{
public:
    int bitwiseComplement(int n)
    {
        if (n == 0)
            return -1;

        int bitLen = 32 - __builtin_clz(n); // n的二进制表示的长度
        int mask = (1 << bitLen) - 1; // 00...011..11，其中1的数量为bitLen
        return ~n & mask;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
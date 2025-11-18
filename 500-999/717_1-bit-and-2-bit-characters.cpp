#include <iostream>
#include <vector>

class Solution
{
public:
    bool isOneBitCharacter(std::vector<int>& bits)
    {
        int n = bits.size();
        if (n == 1)
            return true;

        std::vector<bool> f(n); // f[i]:解码bits[i, n)，最后一个字符是否必须是一比特字符
        f[n - 1] = true;
        f[n - 2] = bits[n - 2] == 0;
        for (int i = n - 3; i >= 0; --i)
        {
            f[i] = (bits[i] == 0 && f[i + 1]) || (bits[i] == 1 && f[i + 2]);
        }
        return f[0];
    }
};

class Solution2
{
public:
    bool isOneBitCharacter(std::vector<int>& bits)
    {
        int n = bits.size(), i = 0;
        while (i < n - 1)   // 循环直到剩下至多一个数字
        {
            i += bits[i] + 1;   // 如果 bits[i] == 1 则跳过下一位
        }
        return i == n - 1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
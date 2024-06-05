#include <iostream>
#include <string>

class Solution
{
public:
    int closestFair(int n)
    {
        int len = std::to_string(n).size();
        // 如果len为奇数，或则无法构造出长度为len且>=n的最小公平整数（例如998 => 1001），
        // 此时答案长度newLen为len+1或len+2，且为1 + newLen/2个0 + (newLen/2 - 1)个1
        int one = (len + 2 - len % 2) / 2;  // one = newLen / 2
        long long ans = std::stoll("1" + std::string(one, '0') + std::string(one - 1, '1'));

        if (len % 2)
            return (int) ans;

        // 假设存在相同位数的解，则最多需要更改后面的len / 2位
        int end = n + quickPow(10, one + 1);
        for (int i = n; i < end; ++i)   // 从低到高枚举，
        {
            int c = 0, j = i;   // c:奇数偶数位数的差值
            while (j > 0)
            {
                int v = j % 10;
                c += v % 2 == 0 ? 1 : -1;
                j = j / 10;
            }
            if (c == 0)
                return i;
        }

        return (int) ans;
    }

private:
    int quickPow(int x, int n)
    {
        int res = 1;
        while (n)
        {
            if (n & 1)
                res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

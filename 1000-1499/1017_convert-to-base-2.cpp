#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::string baseNeg2(int n)
    {
        if (n <= 1)
            return std::to_string(n);

        std::string ans;
        while (n != 0)
        {
            int r = n & 1;
            ans.push_back('0' + r);
            n -= r;
            n /= -2;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

class Solution2
{
public:
    std::string baseNeg2(int n)
    {
        if (n == 0)
            return "1";

        std::string ans;
        int i = 0;
        while ((n >> i) > 0)
        {
            int bit = (n >> i) & 1;
            if (bit && (i % 2))
            {
                n += 1 << (i + 1);
            }
            ans.push_back('0' + bit);
            ++i;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

class Solution3
{
public:
    std::string baseNeg2(int n)
    {
        return baseK(n, -2);
    }

private:
    // 将十进制数n转换为k进制数(k > 0 || k < 0)
    std::string baseK(int n, int k)
    {
        if (n == 0)
            return "0";

        std::string res;
        while (n != 0)
        {
            int r = n % k;
            r = (r + std::abs(k)) % std::abs(k);
            res = std::to_string(r) + res;
            n = (n - r) / k;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

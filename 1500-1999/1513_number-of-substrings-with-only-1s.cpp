#include <iostream>
#include <string>

class Solution
{
public:
    int numSub(std::string s)
    {
        int n = s.size(), begin1 = -1, ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '1')
            {
                if (begin1 == -1)
                {
                    begin1 = i;
                }
            }
            else    // s[i] == '0'
            {
                if (begin1 != -1)   // s[begin1, i)全是'1'
                {
                    ans = (ans + numSub(i - begin1)) % MOD;
                }
                begin1 = -1;
            }
        }
        if (begin1 != -1)
        {
            ans = (ans + numSub(n - begin1)) % MOD;
        }
        return ans;
    }

private:
    static constexpr int MOD = 1'000'000'007;

    // 计算长度为n的字符串一共有多少个子串, MOD 1e9 + 7
    int numSub(long long n)
    {
        // 长度为n的字符串一共会有1+2+...+n = (1+n)*n/2个子串
        return (int) (((1LL + n) * n / 2LL) % MOD);
    }
};

class Solution2
{
public:
    int numSub(std::string s)
    {
        constexpr int MOD = 1'000'000'007;
        long long ans = 0;
        int last0 = -1;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '0')
            {
                last0 = i;
            }
            else
            {
                ans += i - last0;
            }
        }
        return ans % MOD;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
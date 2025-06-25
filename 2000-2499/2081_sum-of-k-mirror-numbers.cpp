#include <iostream>
#include <vector>
#include <numeric>

const int MAX_N = 30;
std::vector<long long> ans[10];

bool isK_Palindrome(long long x, int k)
{
    if (x % k == 0)
    {
        // 如果x % k == 0，则x(x>0)的k进制表示的最低位为0，不可能是回文数
        return false;
    }
    int rev = 0;
    while (rev < x / k)
    {
        rev = rev * k + x % k;
        x /= k;
    }
    return rev == x || rev == x / k;
}

bool doPalindrome(long long x)
{
    bool done = true;
    for (int k = 2; k < 10; ++k)
    {
        if (ans[k].size() < MAX_N && isK_Palindrome(x, k))
        {
            ans[k].push_back(x);
        }
        if (ans[k].size() < MAX_N)
        {
            done = false;
        }
    }
    if (!done)
    {
        return false;
    }

    for (int k = 2; k < 10; ++k)
    {
        // 原地求前缀和
        std::partial_sum(ans[k].begin(), ans[k].end(), ans[k].begin());
    }
    return true;
}

auto init = [](){
    for (int base = 1; ; base *= 10)
    {
        // 生成奇数长度回文数，例如 base = 10，生成的范围是 101 ~ 999
        for (int i = base; i < base * 10; ++i)
        {
            long long x = i;
            for (int t = i / 10; t > 0; t /= 10)
            {
                x = x * 10 + t % 10;
            }
            if (doPalindrome(x))
            {
                return 0;
            }
        }
        // 生成偶数长度回文数，例如 base = 10，生成的范围是 1001 ~ 9999
        for (int i = base; i < base * 10; ++i)
        {
            long long x = i;
            for (int t = i; t > 0; t /= 10)
            {
                x = x * 10 + t % 10;
            }
            if (doPalindrome(x))
            {
                return 0;
            }
        }
    }
}();

class Solution
{
public:
    long long kMirror(int k, int n)
    {
        return ans[k][n - 1];
    }
};
int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

class Solution
{
public:
    using Matrix = std::vector<std::vector<long long>>;

    int numberOfWays(std::string s, std::string t, long long k)
    {
        int n = s.size(), c = kmpSearch(s + s.substr(0, n - 1), t);
        Matrix m = {{c - 1, c}, {n - c, n - 1 - c}};
        m = pow(m, k);
        return (int) m[0][s != t];
    }

private:
    // kmp算法计算前缀表next数组
    void getNext(std::vector<int> &next, const std::string &s)
    {
        // i: 后缀的尾部
        // j+1: 前缀的尾部，同时也是最长相等前后缀的长度
        // next[i]: s[0:i]的最长相等前后缀的长度-1
        next[0] = -1;
        for (int i = 1, j = -1, len = s.size(); i < len; ++i)
        {
            while (j >= 0 && s[i] != s[j + 1])  // 前后缀尾部不相同
                j = next[j];                    // 回退j

            if (s[i] == s[j + 1])               // 前后缀尾部相同
                ++j;                            // 最长相等前后缀的长度+1

            next[i] = j;                        // 记录s[0:i]的最长相等前后缀的长度
        }
    }

    // 获取t在s中的出现次数
    int kmpSearch(const std::string &s, const std::string &t)
    {
        int sLen = s.size(), tLen = t.size(), cnt = 0;
        std::vector<int> next(tLen);
        getNext(next, t);
        for (int i = 0, j = -1; i < sLen; ++i)
        {
            while (j >= 0 && s[i] != t[j + 1])  // // 匹配失败
                j = next[j];                    // 回退到之前匹配的前缀的末尾

            if (s[i] == t[j + 1])               // 匹配成功
                ++j;                            // 准备判断模式串的下一个字符

            if (j == tLen - 1)                  // 找到一个匹配的字串
            {
                ++cnt;
                j = next[j];
            }
        }
        return cnt;
    }

    Matrix multiply(const Matrix &a, const Matrix &b)
    {
        constexpr long long MOD = 1e9 + 7;
        Matrix res(2, std::vector<long long>(2));
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                res[i][j] = (a[i][0] * b[0][j] % MOD + a[i][1] * b[1][j] % MOD) % MOD;
            }
        }
        return res;
    }

    Matrix pow(Matrix m, long long n)
    {
        Matrix res = {{1, 0}, {0, 1}};  // 单位矩阵
        while (n)
        {
            if (n & 1)
                res = multiply(res, m);
            m = multiply(m, m);
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

#include <iostream>
#include <unordered_set>

class Solution
{
public:
    bool queryString(std::string s, int n)
    {
        // 找到n最高位的1，即n的二进制表示的长度
        int nLen = 0;
        int temp = n;
        while (temp > 0)
        {
            temp >>= 1;
            ++nLen;
        }
        std::cout << nLen << std::endl;
        std::unordered_set<int> set;

        int sLen = s.size();
        for (int i = 0; i <= sLen - nLen; ++i)
        {
            for (int j = 0; j < i + nLen; ++j)
            {
                int value = toInt(s, i, j);
                if (value > 0 && value <= n)
                {
                    set.insert(value);
                }
            }
        }

        return set.size() == n;
    }

private:
    int toInt(const std::string &s, int begin, int end)
    {
        int result = 0;
        for (int i = begin; i <= end; ++i)
        {
            result <<= 1;
            result += s[i] - '0';
        }
        return result;
    }
};

class Solution2
{
public:
    bool queryString(std::string s, int n)
    {
        if (n == 1)
        {
            return s.find('1') != std::string::npos;
        }

        // 找到最大的k使得2^k < n
        int k = 30;
        while ((1 << k) >= n)
        {
            --k;
        }

        int sLen = s.size();
        if (sLen < (1 << (k - 1)) + k - 1 || sLen < n - (1 << k) + k + 1)
        {
            return false;
        }
        return help(s, k, 1 << (k - 1), (1 << k) - 1) && help(s, k + 1, 1 << k, n);
    }

private:
    bool help(const std::string &s, int k, int min, int max)
    {
        std::unordered_set<int> set;
        int t = 0;
        for (int r = 0; r < s.size(); ++r)
        {
            t = t * 2 + (s[r] - '0');
            if (r >= k)
            {
                t -= (s[r - k] - '0') << k;
            }
            if (r >= k - 1 && t >= min && t <= max)
            {
                set.insert(t);
            }
        }
        return set.size() == max - min + 1;
    }
};

int main()
{
    Solution solution;
    std::string s = "0110";
    int n = 3;
    bool ans = solution.queryString(s, n);
    std::cout << std::boolalpha;
    return 0;
}
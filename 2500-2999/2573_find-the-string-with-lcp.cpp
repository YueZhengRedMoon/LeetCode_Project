#include <iostream>
#include <vector>

class Solution
{
public:
    std::string findTheString(std::vector<std::vector<int>>& lcp)
    {
        int n = lcp.size();
        std::string s(n, 0);
        int i = 0;  // s[i]没有填字母
        for (char c = 'a'; c <= 'z'; ++c)
        {
            for (int j = i; j < n; ++j)
            {
                if (lcp[i][j])  // s[j] == s[i]
                {
                    s[j] = c;
                }
            }
            // 找下一个空位
            while (i < n && s[i])
            {
                ++i;
            }
            if (i == n) // 没有空位
            {
                break;
            }
        }

        if (i < n)  // 还要空位
        {
            return "";
        }

        // 在上面的计算过程中，我们只访问了 lcp 矩阵中的至多 26 行，其余行完全没有访问过。如果这里面有不匹配的数据呢？
        // 所以构造完 s 后，还需要计算 s 的实际 LCP 矩阵，看看是否和输入的 lcp 矩阵完全一致

        // 验证s是否符合lcp矩阵
        for (i = n - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                // 计算后缀 [i,n-1] 和后缀 [j,n-1] 的实际 LCP
                int actualLCP = s[i] != s[j] ? 0 : (i == n - 1 || j == n - 1 ? 1 : lcp[i + 1][j + 1] + 1);
                if (lcp[i][j] != actualLCP) // 矛盾
                {
                    return "";
                }
            }
        }
        return s;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
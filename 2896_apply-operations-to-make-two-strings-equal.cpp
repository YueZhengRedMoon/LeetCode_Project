#include <iostream>
#include <vector>
#include <functional>

// O(n)记忆化搜索
class Solution
{
public:
    int minOperations(std::string s1, std::string s2, int x)
    {
        int n = s1.size();

        // p[i]:s1[p[i]] != s2[p[i]]
        std::vector<int> p;
        p.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            if (s1[i] != s2[i])
            {
                p.push_back(i);
            }
        }
        int m = p.size();
        if (m % 2)
            return -1;  // 有奇数个位置不相同，s1不可能转换为s2
        if (m == 0)
            return 0;

        std::vector<int> memo(m, -1);
        // i:当前遍历到的不相等数组p的索引
        std::function<int(int)> dfs = [&](int i) -> int
        {
            if (i >= 0 && memo[i] != -1)
                return memo[i];
            if (i == -1)
                // 所有数都已经处理完
                return 0;

            // 第一种操作，花费x/2的代价，将一个数反转
            int res = dfs(i - 1) + x;
            // 第二种操作，花费p[i]-p[i-1]的代价，翻转s1[p[i]]和s1[p[i-1]]
            // 对于两个不相邻的位置s1[p[i]]和s1[p[j]]，可以调用p[i]-p[j]次第二种操作来使s1[p[i]]==s2[p[i]]和s1[p[j]]==s2[p[j]]
            // 例如，对于s1 = 1100, s2 = 0101有1100 -> 1111 -> 1001 -> 0101
            if (i > 0)
            {
                res = std::min(res, dfs(i - 2) + (p[i] - p[i - 1]) * 2);
            }

            return memo[i] = res;
        };

        return dfs(m - 1) / 2;
    }
};

// 记忆化搜索推导为DP，O(n)
class Solution2
{
public:
    int minOperations(std::string s1, std::string s2, int x)
    {
        int n = s1.size();

        // p[i]:s1[p[i]] != s2[p[i]]
        std::vector<int> p;
        p.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            if (s1[i] != s2[i])
            {
                p.push_back(i);
            }
        }
        int m = p.size();
        if (m % 2)
            return -1;  // 有奇数个位置不相同，s1不可能转换为s2
        if (m == 0)
            return 0;

        std::vector<int> f(m + 1);
        f[0] = 0;
        f[1] = x;
        for (int i = 1; i < m; ++i)
        {
            f[i + 1] = std::min(f[i] + x, f[i - 1] + (p[i] - p[i - 1]) * 2);
        }

        return f[m] / 2;
    }
};

// O(n)DP滚动数组优化空间
class Solution3
{
public:
    int minOperations(std::string s1, std::string s2, int x)
    {
        int n = s1.size();

        // p[i]:s1[p[i]] != s2[p[i]]
        std::vector<int> p;
        p.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            if (s1[i] != s2[i])
            {
                p.push_back(i);
            }
        }

        int m = p.size();
        if (m % 2)
            return -1;  // 有奇数个位置不相同，s1不可能转换为s2
        if (m == 0)
            return 0;

        int f0 = 0, f1 = x;
        for (int i = 1; i < m; ++i)
        {
            int newF = std::min(f1 + x, f0 + (p[i] - p[i - 1]) * 2);
            f0 = f1;
            f1 = newF;
        }

        return f1 / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

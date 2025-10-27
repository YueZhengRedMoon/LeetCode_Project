#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    Solution()
    : balanced({1,22,122,212,221,333,1333,3133,3313,3331,4444,14444,22333,23233,23323,
                23332,32233,32323,32332,33223,33232,33322,41444,44144,44414,44441,55555,
                122333,123233,123323,123332,132233,132323,132332,133223,133232,133322,155555,
                212333,213233,213323,213332,221333,223133,223313,223331,224444,231233,231323,
                231332,232133,232313,232331,233123,233132,233213,233231,233312,233321,242444,
                244244,244424,244442,312233,312323,312332,313223,313232,313322,321233,321323,
                321332,322133,322313,322331,323123,323132,323213,323231,323312,323321,331223,
                331232,331322,332123,332132,332213,332231,332312,332321,333122,333212,333221,
                422444,424244,424424,424442,442244,442424,442442,444224,444242,444422,515555,
                551555,555155,555515,555551,666666,1224444})
    {}


    int nextBeautifulNumber(int n)
    {
        return *std::upper_bound(balanced.begin(), balanced.end(), n);
    }

    static std::string createTable()
    {
        std::string table = "{";
        for (int i = 1; i <= 1224444; ++i)
        {
            if (isBalancedNumber(i))
                table += std::to_string(i) + ",";
        }
        table.back() = '}';
        return table;
    }

    static bool isBalancedNumber(int n)
    {
        int cnt[10]{0};
        while (n)
        {
            ++cnt[n % 10];
            n /= 10;
        }
        for (int i = 0; i < 10; ++i)
        {
            if (cnt[i] != 0 && cnt[i] != i)
                return false;
        }
        return true;
    }

private:
    std::vector<int> balanced;
};

class Solution2
{
public:
    int nextBeautifulNumber(int n)
    {
        // 补一个前导零，方便处理答案十进制串比 n 的十进制串长的情况
        std::string s = "0" + std::to_string(n);
        int m = s.size();

        constexpr int MX = 10;
        int cnt[MX]{};  // 每个数字的出现次数
        for (int i = 1; i < m; ++i)
        {
            ++cnt[s[i] - '0'];
        }

        // 从右往左尝试
        for (int i = m - 1; i >= 0; --i)
        {
            if (i > 0)
            {
                --cnt[s[i] - '0'];  // 撤销
            }

            // 增大s[i]为j
            for (int j = s[i] - '0' + 1; j < MX; ++j)
            {
                ++cnt[j];

                // 后面 [i+1, m-1] 需要补满 0 < cnt[k] < k 的数字 k，剩余数位可以随便填
                int free = m - 1 - i;   // 可以随便填的数位个数
                for (int k = 0; k < MX; ++k)
                {
                    int c = cnt[k];
                    if (k < c)  // 不合法
                    {
                        free = -1;
                        break;
                    }
                    if (c > 0)
                    {
                        free -= k - c;
                    }
                }
                if (free < 0)   // 不合法，继续枚举
                {
                    --cnt[j];
                    continue;
                }

                // 对于可以随便填的数位，计算字典序最小的填法
                std::vector<int> a;
                for (int k = 1; k < MX; ++k)
                {
                    if (cnt[k] == 0)
                    {
                        a.push_back(k);
                    }
                }

                auto [missing, ok] = zeroOneKnapsack(a, free);
                if (!ok)    // 无解，继续枚举
                {
                    --cnt[j];
                    continue;
                }

                for (int v : missing)
                {
                    cnt[v] = -v;    // 用负数表示可以随便填的数
                }

                s[i] = '0' + j;
                s.resize(i + 1);
                for (int k = 1; k < MX; ++k)
                {
                    int c = cnt[k];
                    c = c > 0 ? k - c : -c;
                    s += std::string(c, '0' + k);
                }
                return std::stoi(s);
            }
        }

        return -1; // 无解（本题不会发生，但为了可扩展性保留）
    }

private:
    // 从 a 中选一个字典序最小的、元素和等于 target 的子序列
    // a 已经从小到大排序
    // 无解返回 {} 和 false
    std::pair<std::vector<int>, bool> zeroOneKnapsack(const std::vector<int>& a, int target)
    {
        int n = a.size();
        std::vector<bool> f(target + 1);
        f[0] = true;
        std::vector<std::vector<int>> from(n, std::vector<int>(target + 1));

        for (int i = n - 1; i >= 0; --i)
        {
            int v = a[i];
            for (int j = target; j >= v; --j)
            {
                if (f[j - v])
                {
                    f[j] = true;
                    from[i][j] = j - v;
                }
            }
        }

        if (!f[target])
            return {};

        std::vector<int> res;
        for (int i = 0, j = target; j > 0; j = from[i++][j])
        {
            res.push_back(j - from[i][j]);
        }
        return {res, true};
    }
};

int main()
{
    std::cout << Solution::createTable() << std::endl;
    return 0;
}

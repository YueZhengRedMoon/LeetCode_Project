#include <iostream>
#include <unordered_set>
#include <functional>
#include <vector>

namespace TimeLimit
{
    class Solution
    {
    public:
        int findIntegers(int n)
        {
            std::unordered_set<long long> set;
            std::function<void(int)> dfs = [&](long long s) {
                if (s > n || set.find(s) != set.end())
                    return;

                set.insert(s);
                if (s & 1)  // s最低位为1
                {
                    dfs(s << 2);        // xx1 -> xx100
                    dfs((s << 2) + 1);  // xx1 -> xx101
                }
                else    // s最低位为0
                {
                    dfs(s << 2);                // xx0 -> xx000
                    dfs((s << 2) + 1);          // xx0 -> xx001
                    dfs(((s << 1) + 1) << 1);  // xx0 -> xx010
                }
            };
            dfs(0);
            dfs(1);
            dfs(2);
            return static_cast<int>(set.size());
        }
    };
}

class Solution
{
public:
    int findIntegers(int n)
    {
        int m = 32 - __builtin_clz(n);  // n的最高位
        std::vector<std::array<int, 2>> memo(m + 1, {-1, -1});
        std::function<int(int, bool, bool)> dfs = [&](int i, bool pre1, bool isLimit) -> int
        {
            if (i < 0)
                return 1;
            if (!isLimit && memo[i][pre1] >= 0)
                return memo[i][pre1];
            int up = isLimit ? (n >> i) & 1 : 1;
            int res = dfs(i - 1, false, isLimit && up == 0);    // 填0
            if (!pre1 && up == 1)   // 可以填1
            {
                res += dfs(i - 1, true, isLimit);   // 填1
            }
            if (!isLimit)
            {
                memo[i][pre1] = res;
            }
            return res;
        };
        return dfs(m, false, true);
    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

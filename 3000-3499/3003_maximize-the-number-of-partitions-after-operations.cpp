#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

// 可能会超时
class Solution
{
public:
    int maxPartitionsAfterOperations(std::string s, int k)
    {
        std::unordered_map<long long, int> memo;

        // i: 当前位于s[i]
        // mask: 当前前缀包含的不同字母的集合
        // changed: 是否修改过，决定是否能修改s[i]
        // return: 在这一状态下，从剩余未分割的后缀中，可以得到的最大分割数
        std::function<int(int, int, bool)> dfs = [&](int i, int mask, bool changed) -> int {
            if (i == s.size())
            {
                return 1;
            }

            // 把参数压缩到一个 long long 中，方便作为哈希表的 key
            long long args = (long long) i << 32 | mask << 1 | changed;
            auto it = memo.find(args);
            if (it != memo.end())
            {
                // 之前计算过
                return it->second;
            }

            int res;

            // 不改s[i]
            int bit = 1 << (s[i] - 'a');
            int newMask = mask | bit;
            if (__builtin_popcount(newMask) > k)
            {
                // 分割出一个子串，这个子串的最后一个字母是s[i-1]
                // s[i] 作为下一段的第一个字母，也就是 bit 作为下一段的 mask 的初始值
                res = dfs(i + 1, bit, changed) + 1;
            }
            else
            {
                // 不需要分割
                res = dfs(i + 1, newMask, changed);
            }

            if (!changed)
            {
                // 枚举把 s[i] 改成 a,b,c,...,z
                for (int j = 0; j < 26; ++j)
                {
                    newMask = mask | (1 << j);
                    if (__builtin_popcount(newMask) > k)
                    {
                        // 分割出一个子串，这个子串的最后一个字母是s[i-1]
                        // 'a'+j 作为下一段的第一个字母，也就是 1<<j 作为下一段的 mask 的初始值
                        res = std::max(res, dfs(i + 1, 1 << j, true) + 1);
                    }
                    else
                    {
                        // 不需要分割
                        res = std::max(res, dfs(i + 1, newMask, true));
                    }
                }
            }

            return memo[args] = res;    // 记忆化
        };

        return dfs(0, 0, false);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
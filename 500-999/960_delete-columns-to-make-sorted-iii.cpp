#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>

class Solution
{
public:
    int minDeletionSize(std::vector<std::string>& strs)
    {
        // 对于每一行，j列的字母都<=i列的字母吗?
        auto lessEq = [&](int j, int i) -> bool {
            for (std::string_view s : strs)
            {
                if (s[j] > s[i])
                    return false;
            }
            return true;
        };

        int m = strs[0].size();
        std::vector<int> f(m, 0);      // 每个子序列都以i列结尾时，最多保留的列数
        for (int i = 0; i < m; ++i)     // 枚举每一列
        {
            for (int j = 0; j < i; ++j)
            {
                if (f[j] > f[i] && lessEq(j, i))    // 如果f[j] <= f[i]，就不用跑O(n)的lessEq了
                {
                    f[i] = f[j];
                }
            }
            ++f[i];
        }
        return m - *std::max_element(f.begin(), f.end());
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
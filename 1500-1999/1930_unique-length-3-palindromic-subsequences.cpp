#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int countPalindromicSubsequence(std::string s)
    {
        constexpr int MAX_A = 3;

        // 每种字母出现的索引
        bool hasPal[MAX_A][MAX_A]{};  // hasPal[a][b] = true表示存在aba形式的回文子序列
        std::vector<std::vector<int>> idx(MAX_A);
        for (int i = 0; i < s.size(); ++i)
        {
            int j = s[i] - 'a';
            idx[j].push_back(i);
            int cnt = idx[j].size();    // s[i]的出现次数

            if (cnt >= 2)
            {
                if (cnt == 3)
                {
                    hasPal[j][j] = true;
                }

                int l = idx[j][cnt - 2], r = idx[j][cnt - 1];
                if (r - l > 1)
                {
                    for (int k = 0; k < MAX_A; ++k)
                    {
                        auto it = std::upper_bound(idx[k].begin(), idx[k].end(), l);
                        if (it != idx[k].end() && *it < r)
                        {
                            hasPal[j][k] = true;
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < MAX_A; ++i)
        {
            for (int j = 0; j < MAX_A; ++j)
            {
                if (hasPal[i][j])
                    ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::string s = "aabca";
    int ans = solution.countPalindromicSubsequence(s);
    std::cout << ans << std::endl;
    return 0;
}
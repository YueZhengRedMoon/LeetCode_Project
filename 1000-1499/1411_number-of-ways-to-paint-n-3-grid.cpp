#include <iostream>
#include <vector>
#include <unordered_map>

constexpr int MOD = 1'000'000'007;

// 全局 memo，记忆化的内容可以在不同测试数据间共享
std::unordered_map<int, int> memo;

// (i, j)当前位置
// preRow:上一行(i+1行)的颜色
// curRow:当前这一行已填入的颜色
int dfs(int i, int j, int preRow, int curRow)
{
    if (i == 0) // 所有格子都已涂色
    {
        return 1;   // 找到一个合法方案
    }

    if (j == 3) // i 行已涂完色
    {
        // 开始对 i-1 行涂色，curRow 变成 preRow
        return dfs(i - 1, 0, curRow, 0);
    }

    // 参数压缩到一个 int 中
    int key = (i << 14) | (j << 12) | (preRow << 6) | curRow;
    auto it = memo.find(key);
    if (it != memo.end())
    {
        return it->second;
    }

    int res = 0;
    for (int color = 0; color < 3; ++color) // 枚举 (i, j) 的颜色 color
    {
        if ( (preRow > 0 && color == ((preRow >> (j * 2)) & 3))         // 不能和下面相邻格子 (i+1, j) 颜色相同
            || (j > 0 && color == ((curRow >> ((j - 1) * 2)) & 3)) )    // 不能和左侧相邻格子 (i, j-1) 颜色相同
        {
            continue;
        }
        res = (res + dfs(i, j + 1, preRow, curRow | (color << (j * 2)))) % MOD;
    }
    memo[key] = res;    // 记忆化
    return res;
}

class Solution
{
public:
    int numOfWays(int n)
    {
        return dfs(n, 0, 0, 0);
    }
};

int main()
{
    std::string lines1[12] = {"RYR", "YRY", "GRY", "RYG", "YRG", "GRG",
                             "RGR", "YGR", "GYR", "RGY", "YGY", "GYG"};
    char color[3] = {'R', 'G', 'Y'};
    std::vector<std::string> lines2[12];
    int total = 0;
    for (int i = 0; i < 12; ++i)
    {
        std::string tmp(3, 'R');
        for (int c0 = 0; c0 < 3; ++c0)
        {
            for (int c1 = 0; c1 < 3; ++c1)
            {
                for (int c2 = 0; c2 < 3; ++c2)
                {
                    if (c0 != c1 && c1 != c2)
                    {
                        tmp[0] = color[c0];
                        tmp[1] = color[c1];
                        tmp[2] = color[c2];

                        if (lines1[i][0] != tmp[0] && lines1[i][1] != tmp[1] && lines1[i][2] != tmp[2])
                        {
                            lines2[i].push_back(tmp);
                        }
                    }
                }
            }
        }
        total += lines2[i].size();
        std::cout << lines1[i] << " (" << lines2[i].size() << ") :";
        for (const std::string& t : lines2[i])
        {
            std::cout << t << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "total = " << total << std::endl;
    return 0;
}
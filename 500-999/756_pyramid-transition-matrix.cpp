#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    bool pyramidTransition(std::string bottom, std::vector<std::string>& allowed)
    {
        constexpr int MAX_ALPHA = 6;
        std::string groups[MAX_ALPHA][MAX_ALPHA];   // 三角形底部两个字母 -> [三角形顶部字母]
        for (const std::string& s : allowed)
        {
            groups[index(s[0])][index(s[1])].push_back(s[2]);
        }

        int n = bottom.size();
        std::vector<std::string> pyramid(n);
        for (int i = 0; i < n - 1; ++i)
        {
            pyramid[i].resize(i + 1);
        }
        pyramid[n - 1] = std::move(bottom);

        std::unordered_set<std::string> vis;

        // 现在准备填 (i, j) 这个格子，返回继续填能否填完所有格子（从下往上填，每行从左到右填）
        std::function<bool(int, int)> dfs = [&](int i, int j) -> bool {
            if (i < 0)
            {
                // 所有格子都已填完
                return true;
            }

            if (vis.find(pyramid[i]) != vis.end())  // 之前填过一模一样的，这个局部的金字塔无法填完
            {
                return false; // 继续递归也无法填完，直接返回
            }

            if (j > i) // i 行已填完
            {
                vis.insert(pyramid[i]);
                return dfs(i - 1, 0);   // 开始填 i-1 行
            }

            // 枚举 (i, j) 填什么字母，这取决于 (i+1, j) 和 (i+1, j+1) 填的字母
            for (char top : groups[index(pyramid[i + 1][j])][index(pyramid[i + 1][j + 1])])
            {
                pyramid[i][j] = top;
                if (dfs(i, j + 1))
                {
                    return true;
                }
            }
            return false;
        };

        return dfs(n - 2, 0);
    }

private:
    int index(char a)
    {
        return a - 'A';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
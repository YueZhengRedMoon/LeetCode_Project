#include <iostream>
#include <vector>
#include <functional>
#include "../debug/debug.h"

class Solution
{
public:
    int maximumRows(std::vector<std::vector<int>> &matrix, int numSelect)
    {
        int m = matrix.size(), n = matrix[0].size(), ans = 0;
        std::vector<int> rows(m, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    rows[i] |= 1 << j;
                }
            }
        }

        // 枚举列
        std::function<void(int, int, int)> backtracking = [&](int begin, int remain, int cols) {
            if (remain == 0)
            {
                int cnt = 0;
                for (int i = 0; i < m; ++i)
                {
                    if ((rows[i] | cols) == cols)
                        ++cnt;
                }
                if (cnt > ans)
                    ans = cnt;
                return;
            }
            // 剩下的列全选上也凑不齐足够的列数
            else if (n - begin + 1 < remain)
                return;

            for (int i = begin; i < n; ++i)
            {
                backtracking(i + 1, remain - 1, cols | (1 << i));
            }
        };

        backtracking(0, numSelect, 0);

        return ans;
    }
};

class Solution2
{
public:
    int maximumRows(std::vector<std::vector<int>> &matrix, int numSelect)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<int> rows(m, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (matrix[i][n - j])
                {
                    rows[i] |= 1 << (j - 1);
                }
            }
        }

        int begin = (1 << numSelect) - 1;
        int end = begin << (n - numSelect);
        int cols = begin;
        int ans = 0;
        while (cols <= end)
        {
            std::cout << "cols = ";
            debug::printBinaryValue<3>(cols);

            int cnt = 0;
            // 遍历每一行
            for (int row : rows)
            {
                if ((row | cols) == cols)
                {
                    ++cnt;
                }
            }

            if (cnt > ans)
                ans = cnt;

            int lowBit = cols & -cols;
            int left = cols + lowBit;
            int right = (cols ^ (cols + lowBit)) / lowBit >> 2;
            cols = left | right;
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::vector<int>> matrix = {{0,0,0},{1,0,1},{0,1,1},{0,0,1}};
    int numSelect = 2;
    int ans = solution.maximumRows(matrix, numSelect);
    std::cout << ans << std::endl;
    return 0;
}
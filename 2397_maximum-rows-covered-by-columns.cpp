#include <iostream>
#include <vector>
#include <functional>

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

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
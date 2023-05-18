#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    void rotate(std::vector<std::vector<int>> &matrix)
    {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < n - i * 2 - 1; ++j)
            {
                int temp1, temp2;
                temp1 = matrix[i + j][n - i - 1];               // 暂存右上角的值
                matrix[i + j][n - i - 1] = matrix[i][i + j];    // 将左上角的值赋值给右上角
                temp2 = matrix[n - i - 1][n - i - 1 - j];       // 暂存右下角的值
                matrix[n - i - 1][n - i - 1 - j] = temp1;       // 将原右上角的值赋值给右下角
                temp1 = matrix[n - i - 1 - j][i];               // 暂存左下角的值
                matrix[n - i - 1 - j][i] = temp2;               // 将原右下角的值赋值给左下角
                matrix[i][i + j] = temp1;                       // 将原来左下角的值赋值给左上角
            }
        }
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    debug::printVector2D(matrix);
    std::cout << std::endl;
    solution.rotate(matrix);
    debug::printVector2D(matrix);
    return 0;
}

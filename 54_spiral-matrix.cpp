#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<int> ans(m * n);
        const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        const int visited = 404;
        for (int i = 0, x = 0, y = 0, curDir = 0; i < m * n; ++i)
        {
            ans[i] = matrix[x][y];
            matrix[x][y] = visited;
            int nextX = x + dir[curDir][0];
            int nextY = y + dir[curDir][1];
            if (nextX < 0 || nextX >= m || nextY < 0 || nextY >= n || matrix[nextX][nextY] == visited)
            {
                curDir = (curDir + 1) % 4;
                nextX = x + dir[curDir][0];
                nextY = y + dir[curDir][1];
            }
            x = nextX;
            y = nextY;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

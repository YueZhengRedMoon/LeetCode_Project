#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid, int k)
    {
        int m = grid.size(), n = grid[0].size();
        auto reverse = [&](int l, int r) -> void {
            while (l < r)
            {
                int x1 = l / n, y1 = l % n;
                int x2 = r / n, y2 = r % n;
                std::swap(grid[x1][y1], grid[x2][y2]);
                ++l;
                --r;
            }
        };

        int size = m * n;
        k %= size;  // 轮转 k 次等同于轮转 k % size 次
        reverse(0, size - 1);
        reverse(0, k - 1);
        reverse(k, size - 1);
        return grid;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
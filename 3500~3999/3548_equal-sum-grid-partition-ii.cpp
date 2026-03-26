#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        long long sum = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                sum += grid[i][j];
            }
        }

        long long upSum = 0, leftSum = 0, downSum = 0, rightSum = 0, delta;

        // 从左到右，从上到下枚举
        std::unordered_set<long long> set;
        std::vector<long long> colSum(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int x = grid[i][j];
                upSum += x;
                colSum[j] += x;
                set.insert(x);

                if (j == n - 1) // 枚举到了最后一列
                {
                    downSum = sum - upSum;
                    if (upSum == downSum)
                    {
                        return true;
                    }
                    // 尝试删除上半区的一个元素
                    delta = upSum - downSum;
                    if (set.find(delta) != set.end())
                    {
                        // 如果上半区只有一行，除非总共只有2列，否则删除的元素必须是第0列或第n-1列的元素，不然会使上半区不连通
                        if (i == 0 && n > 2 && grid[0][0] != delta && grid[0][n - 1] != delta)
                        {
                            continue;
                        }
                        // 如果上半区只有一列，除非总共只有2行，否则删除的元素必须第0行或者第i行的元素，不然会使上半区不连通
                        if (n == 1 && i > 1 && grid[0][0] != delta && grid[i][0] != delta)
                        {
                            continue;
                        }
                        return true;
                    }
                }

                if (i == m - 1) // 枚举到了最后一行
                {
                    leftSum += colSum[j];
                    rightSum = sum - leftSum;
                    if (leftSum == rightSum)
                    {
                        return true;
                    }

                    // 尝试删除左半区的一个元素
                    delta = leftSum - rightSum;
                    if (set.find(delta) != set.end())
                    {
                        // 如果左半区只有一列，除非总共只有2行，否则删除的元素必须是第0行或第m-1行的元素，不然会使左半区不连通
                        if (j == 0 && m > 2 && grid[0][0] != delta && grid[m - 1][0] != delta)
                        {
                            continue;
                        }
                        // 如果左半区只有一行，除非总共只有2列，否则删除的元素必须是第0列或第j列的元素，不然会使左半区不连通
                        if (m == 1 && j > 1 && grid[0][0] != delta && grid[0][j] != delta)
                        {
                            continue;
                        }
                        return true;
                    }
                }
            }
        }

        // 重置
        set.clear();    // 清空set
        std::fill(colSum.begin(), colSum.end(), 0); // 重置colSum
        downSum = 0;

        // 从右到左，从下到上枚举
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                int x = grid[i][j];
                downSum += x;
                colSum[j] += x;
                set.insert(x);

                if (j == 0) // 枚举到了第0列
                {
                    upSum = sum - downSum;
                    if (upSum == downSum)
                    {
                        return true;
                    }
                    // 尝试删除下半区的一个元素
                    delta = downSum - upSum;
                    if (set.find(delta) != set.end())
                    {
                        // 如果下半区只有一行，除非总共只有2列，否则删除的元素必须是第0列或第n-1列的元素，不然会使下半区不连通
                        if (i == m - 1 && n > 2 && grid[m - 1][0] != delta && grid[m - 1][n - 1] != delta)
                        {
                            continue;
                        }
                        // 如果下半区只有一列，除非总共只有2行，否则删除的元素必须第m-1行或者第i行的元素，不然会使下半区不连通
                        if (n == 1 && i < m - 2 && grid[m - 1][0] != delta && grid[i][0] != delta)
                        {
                            continue;
                        }
                        return true;
                    }
                }

                if (i == 0) // 枚举到了第0行
                {
                    rightSum += colSum[j];
                    leftSum = sum - rightSum;
                    if (leftSum == rightSum)
                    {
                        return true;
                    }
                    // 尝试删除右半区的一个元素
                    delta = rightSum - leftSum;
                    if (set.find(delta) != set.end())
                    {
                        // 如果右半区只有一列，除非总共只有2行，否则删除的元素必须是第0行或第m-1行的元素，不然会使右半区不连通
                        if (j == n - 1 && m > 2 && grid[0][n - 1] != delta && grid[m - 1][n - 1] != delta)
                        {
                            continue;
                        }
                        // 如果右半区只有一行，除非总共只有2列，否则删除的元素必须是第n-1列或第j列的元素，不然会使右半区不连通
                        if (m == 1 && j < n - 2 && grid[0][n - 1] != delta && grid[0][j] != delta)
                        {
                            continue;
                        }
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{10,5,4,5}};
    bool ans = solution.canPartitionGrid(grid);
    std::cout << ans << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>

class Solution
{
public:
    int maxIncreasingCells(std::vector<std::vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size();
        std::map<int, std::vector<std::pair<int, int>>> g;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                g[mat[i][j]].emplace_back(i, j);    // 相同元素放在同一组，统计位置
            }
        }

        std::vector<int> rowMax(m), colMax(n);
        for (auto& [_, pos] : g)
        {
            // 先把所有f值计算出来，再更新rowMax和colMax
            std::vector<int> fs;
            fs.reserve(pos.size());
            for (auto& [i, j] : pos)
                fs.push_back(std::max(rowMax[i], colMax[j]) + 1);
            for (int k = 0; k < pos.size(); ++k)
            {
                auto& [i, j] = pos[k];
                rowMax[i] = std::max(rowMax[i], fs[k]); // 更新第i行的最大f值
                colMax[j] = std::max(colMax[j], fs[k]); // 更新第j列的最大f值
            }
        }

        return *std::max_element(rowMax.begin(), rowMax.end());
    }
};

namespace WrongAnswer
{
    struct Grid
    {
        int nextRow{-1};
        int nextCol{-1};
        int maxVisit{1};
        int inDeg{0};
    };

    class Solution
    {
    public:
        using Pair = std::pair<int, int>;

        int maxIncreasingCells(std::vector<std::vector<int>>& mat)
        {
            int m = mat.size(), n = mat[0].size();
            std::vector<std::vector<Grid>> grids(m, std::vector<Grid>(n));
            std::vector<int> col(n);
            for (int i = 0; i < m; ++i)
            {
                std::iota(col.begin(), col.end(), 0);
                std::sort(col.begin(), col.end(), [&](int j1, int j2) {return mat[i][j1] < mat[i][j2];});
                for (int k = n - 2; k >= 0; --k)
                {
                    if (mat[i][col[k]] < mat[i][col[k + 1]])
                    {
                        int nextJ = grids[i][col[k]].nextCol = col[k + 1];
                        ++grids[i][nextJ].inDeg;
                    }
                    else if (mat[i][col[k]] == mat[i][col[k + 1]])
                    {
                        int nextJ = grids[i][col[k]].nextCol = grids[i][col[k + 1]].nextCol;
                        if (nextJ != -1)
                            ++grids[i][nextJ].inDeg;
                    }
                }
            }
            std::vector<int> row(m);
            for (int j = 0; j < n; ++j)
            {
                std::iota(row.begin(), row.end(), 0);
                std::sort(row.begin(), row.end(), [&](int i1, int i2) {return mat[i1][j] < mat[i2][j];});
                for (int k = m - 2; k >= 0; --k)
                {
                    if (mat[row[k]][j] < mat[row[k + 1]][j])
                    {
                        int nextI = grids[row[k]][j].nextRow = row[k + 1];
                        ++grids[nextI][j].inDeg;
                    }
                    else if (mat[row[k]][j] == mat[row[k + 1]][j])
                    {
                        int nextI = grids[row[k]][j].nextRow = grids[row[k + 1]][j].nextRow;
                        if (nextI != -1)
                            ++grids[nextI][j].inDeg;
                    }
                }
            }

            int ans = 0;
            std::queue<Pair> queue;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (grids[i][j].inDeg == 0)
                        queue.emplace(i, j);
                }
            }
            while (!queue.empty())
            {
                auto [i, j] = queue.front();
                queue.pop();
                ans = std::max(ans, grids[i][j].maxVisit);
                int visit = grids[i][j].maxVisit + 1, nextI = grids[i][j].nextRow, nextJ = grids[i][j].nextCol;
                if (nextI != -1 && visit > grids[nextI][j].maxVisit)
                {
                    grids[nextI][j].maxVisit = visit;
                    queue.emplace(nextI, j);
                }
                if (nextJ != -1 && visit > grids[i][nextJ].maxVisit)
                {
                    grids[i][nextJ].maxVisit = visit;
                    queue.emplace(i, nextJ);
                }
            }

            return ans;
        }
    };

}

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat({{2, -4, 2, -2, 6}});
    int ans = solution.maxIncreasingCells(mat);
    std::cout << ans << std::endl;
    return 0;
}

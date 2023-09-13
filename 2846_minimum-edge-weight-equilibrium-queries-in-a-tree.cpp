#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    std::vector<int> minOperationsQueries(int n, std::vector<std::vector<int>> &edges,
                                          std::vector<std::vector<int>> &queries)
    {
        // 建图, first:节点编号, second: 边的权值
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const std::vector<int> &edge : edges)
        {
            int x = edge[0], y = edge[1], w = edge[2] - 1;
            graph[x].emplace_back(y, w);
            graph[y].emplace_back(x, w);
        }

        // 树上倍增数组
        //  - 总共有n个节点，树中每个节点至多有2^log(n)个祖先节点
        const int m = bitLength(n), MAX_W = 26;
        //  - pa[x][i]: 从x出发，经过2^i个节点到达的节点
        std::vector<std::vector<int>> pa(n, std::vector<int>(m, -1));
        //  - cnt[x][i][w]: 从x出发，经过2^i个节点，途中经过的权值为w的边的数量
        std::vector<std::vector<std::vector<int>>> cnt(n, std::vector<std::vector<int>>(m, std::vector<int>(MAX_W, 0)));
        // 每个节点的深度
        std::vector<int> depth(n, 0);

        std::function<void(int, int)> dfs = [&](int x, int fa) -> void
        {
            pa[x][0] = fa;  // 初始化树上倍增算法中x的父节点
            for (auto [y, w] : graph[x])    // 遍历与x连接的边, 它们将是x的子节点
            {
                if (y != fa)    // 避免将父节点作为子节点
                {
                    cnt[y][0][w] = 1;
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        // 树上倍增
        for (int i = 0; i < m - 1; ++i)
        {
            for (int x = 0; x < n; ++x)
            {
                int p = pa[x][i];
                if (p != -1)
                {
                    pa[x][i + 1] = pa[p][i];
                    for (int j = 0; j < MAX_W; ++j)
                    {
                        cnt[x][i + 1][j] = cnt[x][i][j] + cnt[p][i][j];
                    }
                }
            }
        }

        int queriesNum = queries.size();
        std::vector<int> ans(queriesNum);
        for (int q = 0; q < queriesNum; ++q)
        {
            std::vector<int> cw(MAX_W, 0);  // 从x到y经过的每一种权值的边的种数
            int x = queries[q][0], y = queries[q][1];
            // 为便于统一处理，使x的深度小于y的深度
            if (depth[x] > depth[y])
                std::swap(x, y);
            // 从x到y经过的路径长度(边的数量)，最后要减去2 * depth[lca], lca是x与y的最近公共祖先
            int pathLen = depth[x] + depth[y];
            // y比x深k层
            int k = depth[y] - depth[x];
            // 将y提升到与x在同一层
            for (int i = 0, end = bitLength(k); i < end; ++i)
            {
                if ((k >> i) & 1)
                {
                    for (int j = 0; j < MAX_W; ++j)
                        cw[j] += cnt[y][i][j];
                    y = pa[y][i];
                }
            }

            // 现在x, y在同一深度，如果它们不相同，则同步向上找x与y的最近公共祖先
            if (x != y)
            {
                for (int i = m - 1; i >= 0; --i)
                {
                    int px = pa[x][i], py = pa[y][i];
                    if (px != py)
                    {
                        for (int j = 0; j < MAX_W; ++j)
                            cw[j] += cnt[x][i][j] + cnt[y][i][j];
                        x = px;
                        y = py;
                    }
                }
                for (int j = 0; j < MAX_W; ++j)
                    cw[j] += cnt[x][0][j] + cnt[y][0][j];
                x = pa[x][0];
            }

            int lca = x;
            pathLen -= depth[lca] * 2;
            ans[q] = pathLen - *std::max_element(cw.begin(), cw.end());
        }

        return ans;
    }

private:
    int bitLength(int n)
    {
        return n == 0 ? 0 : 32 - __builtin_clz(n);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

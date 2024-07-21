#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

namespace WrongAnswer
{
    class UnionSet
    {
    public:
        UnionSet(int n) : parent(n), rank(n)
        {
            std::iota(parent.begin(), parent.end(), 0);
        }

        int find(int x)
        {
            if (x == parent[x])
                return x;
            else
                return parent[x] = find(parent[x]);
        }

        void unite(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x == y)
                return;
            if (rank[x] < rank[y])
            {
                parent[x] = y;
            }
            else
            {
                parent[y] = x;
                if (rank[x] == rank[y])
                    ++rank[x];
            }
        }

    private:
        std::vector<int> parent;
        std::vector<int> rank;
    };

    class Solution
    {
    public:
        int maximumDetonation(std::vector<std::vector<int>>& bombs)
        {
            int n = bombs.size();
            UnionSet unionSet(n);
            for (int i = 0; i < n - 1; ++i)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    if (isIntersect(bombs[i], bombs[j]))
                    {
                        std::cout << bombs[i][0] << ' ' << bombs[i][1] << ' ' << bombs[i][2] << std::endl;
                        std::cout << bombs[j][0] << ' ' << bombs[j][1] << ' ' << bombs[j][2] << std::endl;
                        unionSet.unite(i, j);
                    }
                }
            }

            int ans = 1;
            std::unordered_map<int, int> setSize;
            for (int i = 0; i < n; ++i)
            {
                int x = unionSet.find(i);
                ans = std::max<int>(ans, ++setSize[x]);
            }
            return ans;
        }

    private:
        bool isIntersect(const std::vector<int>& p1, const std::vector<int>& p2)
        {
            long long x1 = p1[0], y1 = p1[1], r1 = p1[2], x2 = p2[0], y2 = p2[1], r2 = p2[2];
            return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
        }
    };
}

class Solution
{
public:
    int maximumDetonation(std::vector<std::vector<int>>& bombs)
    {
        int n = bombs.size();
        std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    g[i][j] = check(bombs[i], bombs[j]);
                }
            }
        }

        int ans = 1;
        std::vector<bool> visit(n);
        for (int x = 0; x < n; ++x)
        {
            std::fill(visit.begin(), visit.end(), false);
            ans = std::max(ans, dfs(g, x, visit));
        }
        return ans;
    }

private:
    // 返回b1爆炸是否会引爆b2
    bool check(const std::vector<int>& b1, const std::vector<int>& b2)
    {
        long long x1 = b1[0], y1 = b1[1], r1 = b1[2], x2 = b2[0], y2 = b2[1];
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= r1 * r1;
    }

    int dfs(const std::vector<std::vector<bool>>& g, int x, std::vector<bool>& visit)
    {
        visit[x] = true;
        int res = 1;
        for (int y = 0; y < g[x].size(); ++y)
        {
            if (g[x][y] && !visit[y])
            {
                res += dfs(g, y, visit);
            }
        }
        return res;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> bombs = {{54,95,4},{99,46,3},{29,21,3},{96,72,8},{49,43,3},
                                           {11,20,3},{2,57,1},{69,51,7},{97,1,10},{85,45,2},
                                           {38,47,1},{83,75,3},{65,59,3},{33,4,1},{32,10,2},
                                           {20,97,8},{35,37,3}};
    int ans = solution.maximumDetonation(bombs);
    std::cout << ans << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

namespace Solution_0X3F
{
    class UnionFind
    {
    public:
        int cc; // 连通块个数

        UnionFind(int n) : fa(n), cc(n)
        {
            // 一开始有 n 个集合 {0}, {1}, ..., {n-1}
            // 集合 i 的代表元是自己
            std::iota(fa.begin(), fa.end(), 0);
        }

        // 返回 x 所在集合的代表元
        // 同时做路径压缩，也就是把 x 所在集合中的所有元素的 fa 都改成代表元
        int find(int x)
        {
            // 如果 fa[x] == x，则表示 x 是代表元
            if (fa[x] != x)
            {
                fa[x] = find(fa[x]);    // fa 改成代表元
            }
            return fa[x];
        }

        // 把 from 所在集合合并到 to 所在集合中，返回是否合并成功
        bool merge(int from, int to)
        {
            int x = find(from), y = find(to);
            if (x == y) // from 和 to 在同一个集合，不做合并
            {
                return false;
            }
            fa[x] = y;  // 合并集合。修改后就可以认为 from 和 to 在同一个集合了
            --cc;       // 成功合并，连通块个数减一
            return true;
        }

    private:
        std::vector<int> fa;    // 代表元
    };

    class Solution
    {
    public:
        int maxStability(int n, std::vector<std::vector<int>>& edges, int k)
        {
            UnionFind mustUF(n);    // 必选边并查集
            UnionFind allUF(n);     // 全图并查集
            int minS = INT_MAX, maxS = 0;
            for (const std::vector<int>& e : edges)
            {
                int x = e[0], y = e[1], s = e[2], must = e[3];
                if (must && !mustUF.merge(x, y))    // 必选边成环
                {
                    return -1;
                }
                allUF.merge(x, y);
                minS = std::min(minS, s);
                maxS = std::max(maxS, s);
            }

            if (allUF.cc > 1)   // 图不连通
            {
                return -1;
            }

            // 检查是否可以通过至多k次升级构成生成树，使生成树边的最小权值 >= low
            auto check = [&](int low) -> bool {
                UnionFind u(n);
                for (const std::vector<int>& e : edges)
                {
                    int x = e[0], y = e[1], s = e[2], must = e[3];
                    if (must && s < low)    // 必选边的边权太小
                    {
                        return false;
                    }
                    if (must || s >= low)
                    {
                        u.merge(x, y);
                    }
                }

                int leftK = k;
                for (const std::vector<int>& e : edges)
                {
                    if (leftK == 0 || u.cc == 1)
                    {
                        break;  // 已无可用升级次数，或者图已联通
                    }
                    int x = e[0], y = e[1], s = e[2], must = e[3];
                    if (!must && s < low && s * 2 >= low && u.merge(x, y))
                    {
                        --leftK;
                    }
                }
                return u.cc == 1;
            };

            int left = minS, right = maxS * 2 + 1;
            while (left + 1 < right)
            {
                int mid = left + (right - left) / 2;
                (check(mid) ? left : right) = mid;
            }
            return left;
        }
    };
}

class UnionSet
{
public:
    int connectComponent;   // 连通块的数量

    UnionSet(int n) : parent(n), connectComponent(n)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    // 合并x和y所属的集合，返回是否合并成功
    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return false;
        }
        else
        {
            parent[y] = x;
            --connectComponent;
            return true;
        }
    }

private:
    std::vector<int> parent;
};

class Solution
{
public:
    int maxStability(int n, std::vector<std::vector<int>>& edges, int k)
    {
        UnionSet mustUS(n); // 必选边并查集
        UnionSet allUS(n);  // 全图并查集
        int minS = INT_MAX, maxS = 0;
        for (const std::vector<int>& e : edges)
        {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (must && !mustUS.unite(u, v))    // 必须边构成环
            {
                return -1;
            }
            allUS.unite(u, v);
            if (s < minS)
                minS = s;
            if (s > maxS)
                maxS = s;
        }
        if (allUS.connectComponent > 1) // 图不连通
        {
            return -1;
        }

        // 检查是否可以通过至多k次升级构成生成树，使生成树边的最小权值 >= low
        auto check = [&](int low) -> bool {
            UnionSet unionSet(n);
            // 将所有必选边和s>=low的边加入到图中
            for (const std::vector<int>& e : edges)
            {
                int u = e[0], v = e[1], s = e[2], must = e[3];
                if (must && s < low)    // 必选边权值太小
                {
                    return false;
                }
                if (must || s >= low)
                {
                    unionSet.unite(u, v);
                }
            }

            int leftK = k;
            // 遍历所有可升级的边
            for (const std::vector<int>& e : edges)
            {
                if (leftK == 0 || unionSet.connectComponent == 1)   // 已无可用升级次数 或 图已连通
                {
                    break;
                }
                int u = e[0], v = e[1], s = e[2], must = e[3];
                if (!must && s < low && s * 2 >= low && unionSet.unite(u, v))
                {
                    --leftK;
                }
            }
            return unionSet.connectComponent == 1;
        };

        int left = minS, right = maxS * 2 + 1, ans = -1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (check(mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int maxStability(int n, std::vector<std::vector<int>>& edges, int k)
    {
        UnionSet unionSet(n);
        UnionSet allUS(n);
        int minS1 = INT_MAX;
        for (const std::vector<int>& e : edges)
        {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (must)
            {
                if (!unionSet.unite(u, v))  // 必选边成环
                {
                    return -1;
                }
                if (s < minS1)
                    minS1 = s;
            }
            allUS.unite(u, v);
        }

        if (allUS.connectComponent > 1) // 图不连通
        {
            return -1;
        }

        if (unionSet.connectComponent == 1) // 只需选必选边
        {
            return minS1;
        }

        // Kruskal 求最大生成树
        // 将边按照s从大到小排序
        std::sort(edges.begin(), edges.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {return a[2] > b[2];});
        std::vector<int> a;
        for (const std::vector<int>& e : edges)
        {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (!must && unionSet.unite(u, v))  // 边(u,v)不是必选边，且u,v不处于同一个连通块中
            {
                a.push_back(s);
            }
        }

        // 答案为如下三者的最小值：
        // 1. must = 1 中的最小边权
        // 2. a 中最小边权 * 2
        // 3. a 中第 k+1 小边权
        int m = a.size();
        int ans = std::min(minS1, a[m - 1] * 2);
        if (k < m)
        {
            ans = std::min(ans, a[m - 1 - k]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include "debug.h"

const int MAX_NUM = 51;
std::vector<int> coprime[MAX_NUM];
int init = []{
    // 预处理：coprime[i]保存[1, MAX_NUM)中与i互质的所有元素
    for (int i = 1; i < MAX_NUM; ++i)
    {
        for (int j = 1; j < MAX_NUM; ++j)
        {
            if (std::gcd(i, j) == 1)
                coprime[i].push_back(j);
        }
    }
    return 0;
}();

class Solution
{
public:
    std::vector<int> getCoprimes(std::vector<int>& nums, std::vector<std::vector<int>>& edges)
    {
        int n = nums.size();
        g.resize(n);
        for (auto &e : edges)
        {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        ans.resize(n, -1);
        dfs(0, -1, 1, nums);
        return ans;
    }

private:
    std::vector<std::vector<int>> g;
    std::vector<int> ans;
    // valDepthId[j].first:dfs遍历到当前节点（节点值=i）, 节点值等于j（gcd(i, j) == 1）的最近祖先的深度
    // valDepthId[j].second:dfs遍历到当前节点（节点值=i）, 节点值等于j（gcd(i, j) == 1）的最近祖先的节点编号
    std::pair<int, int> valDepthId[MAX_NUM];

    void dfs(int x, int fa, int depth, const std::vector<int>& nums)
    {
        int val = nums[x];  // x的节点值
        // 计算与val互质的数中，深度最大的节点编号
        int maxDepth = 0;
        for (int j : coprime[val])
        {
            auto [d, id] = valDepthId[j];
            if (d > maxDepth)
            {
                maxDepth = d;
                ans[x] = id;
            }
        }

        auto tmp = valDepthId[val]; // 恢复现场
        valDepthId[val] = {depth, x};   // 保存val对应的节点深度和节点编号
        for (int y : g[x])
        {
            if (y != fa)
                dfs(y, x, depth + 1, nums);
        }
        valDepthId[val] = tmp;  // 恢复现场
    }
};

namespace WrongAnswer
{
    class Solution
    {
    public:
        std::vector<int> getCoprimes(std::vector<int>& nums, std::vector<std::vector<int>>& edges)
        {
            int n = nums.size();
            // 建图
            std::vector<std::vector<int>> g(n);
            for (const auto& e : edges)
            {
                int x = e[0], y = e[1];
                g[x].push_back(y);
                g[y].push_back(x);
            }

            int m = 32 - __builtin_clz(n);
            int maxVal = 1; // 最大的节点值
            std::vector<std::vector<int>> p(n, std::vector<int>(m + 1, -1));    // 祖先节点
            std::vector<int> depth(n);  // 每个节点的深度

            // dfs计算每个节点的父节点和深度
            std::function<void(int, int, int)> dfs = [&](int x, int fa, int d) {
                if (nums[x] > maxVal)
                    maxVal = nums[x];
                depth[x] = d++;
                for (int y : g[x])
                {
                    if (y != fa)
                    {
                        p[y][0] = x;
                        dfs(y, x, d);
                    }
                }
            };
            dfs(0, -1, 0);

            // 树上倍增计算祖先节点
            for (int x = 0; x < n; ++x)
            {
                for (int i = 1; i <= m; ++i)
                {
                    if (p[x][i - 1] != -1)
                    {
                        p[x][i] = p[p[x][i - 1]][i - 1];
                    }
                }
            }

            // 统计每种值对应的节点
            std::vector<std::vector<int>> valNodes(maxVal + 1);
            for (int i = 0; i < n; ++i)
                valNodes[nums[i]].push_back(i);
            // 将节点按深度从高到低排序
            for (int v = 1; v <= maxVal; ++v)
            {
                std::sort(valNodes[v].begin(), valNodes[v].end(), [&](int x, int y) {return depth[x] > depth[y];});
            }

            std::vector<int> ans(n, -1);
            for (int x = 1; x < n; ++x)
            {
                int a = nums[x];
                for (int b = 1; b <= maxVal; ++b)
                {
                    if (gcd(a, b) == 1)
                    {
                        const std::vector<int>& valNode = valNodes[b];
                        auto it = std::upper_bound(valNode.begin(), valNode.end(), x, [&](int x, int y) {return depth[x] > depth[y];});
                        while (it != valNode.end())
                        {
                            int y = *it;
                            if (isAncestor(x, y, depth[x] - depth[y], p))
                            {
                                if (ans[x] == -1 || depth[y] > depth[ans[x]])
                                    ans[x] = y;
                            }
                            ++it;
                        }
                    }
                }
            }
            return ans;
        }

    private:
        // 验证y是否是x的祖先节点，假设x的深度 - y的深度 > 0 = d
        bool isAncestor(int x, int y, int d, const std::vector<std::vector<int>>& p)
        {
            int i = 0;
            while (d && x >= 0)
            {
                if (d & 1)
                {
                    x = p[x][i];
                }
                d >>= 1;
                ++i;
            }
            return x == y;
        }

        int gcd(int a, int b)
        {
            while (b != 0)
            {
                int r = a % b;
                a = b;
                b = r;
            }
            return a;
        }
    };
}

int main()
{
    Solution solution;
    std::vector<int> nums = {9,16,30,23,33,35,9,47,39,46,16,38,5,49,21,44,17,1,6,37,49,15,23,46,
                             38,9,27,3,24,1,14,17,12,23,43,38,12,4,8,17,11,18,26,22,49,14,9};
    std::vector<std::vector<int>> edges = {{17,0},{30,17},{41,30},{10,30},{13,10},{7,13},{6,7},{45,10},{2,10},{14,2},
                                           {40,14},{28,40},{29,40},{8,29},{15,29},{26,15},{23,40},{19,23},{34,19},
                                           {18,23},{42,18},{5,42},{32,5},{16,32},{35,14},{25,35},{43,25},{3,43},{36,25},
                                           {38,36},{27,38},{24,36},{31,24},{11,31},{39,24},{12,39},{20,12},{22,12},
                                           {21,39},{1,21},{33,1},{37,1},{44,37},{9,44},{46,2},{4,46}};
    std::vector<int> ans = solution.getCoprimes(nums, edges);
    debug::printVector(ans);
    return 0;
}

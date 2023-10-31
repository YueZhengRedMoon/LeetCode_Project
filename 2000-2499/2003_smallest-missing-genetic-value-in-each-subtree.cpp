#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include <stack>

// DFS
class Solution
{
public:
    std::vector<int> smallestMissingValueSubtree(std::vector<int> &parents, std::vector<int> &nums)
    {
        int n = parents.size();
        std::vector<int> ans(n, 1); // 子树中如果没有基因值为1的节点，则以i为根节点的子树缺失的最小基因值为1
        auto it = std::find(nums.begin(), nums.end(), 1);
        if (it == nums.end())   // 不存在基因值为1的节点
            return ans;

        // 建树
        std::vector<std::vector<int>> g(n);
        for (int i = 1; i < n; ++i)
            g[parents[i]].push_back(i);

        std::unordered_set<int> vis;
        // 遍历以x为根的子树，获取以x为根的子树的基因值集合
        std::function<void(int)> dfs = [&](int x) -> void {
            vis.insert(nums[x]);    // 标记基因值
            for (int child : g[x])
            {
                if (vis.find(nums[child]) == vis.end())
                {
                    dfs(child);
                }
            }
        };

        int minMiss = 2;                // 缺失的最小基因值
        int node = it - nums.begin();   // 基因值为1的节点
        // 从基因值为1的节点开始从下往上走
        while (node >= 0)
        {
            dfs(node);  // 遍历以node为根节点的子树，获取子树中的基因值集合
            // 找到缺失的最小基因值
            while (vis.find(minMiss) != vis.end())  // 以node为根的子树包含这个基因值
                ++minMiss;

            ans[node] = minMiss;    // 记录答案
            node = parents[node];   // 向上走
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> smallestMissingValueSubtree(std::vector<int> &parents, std::vector<int> &nums)
    {
        int n = parents.size();
        std::vector<int> ans(n, 1); // 子树中如果没有基因值为1的节点，则以i为根节点的子树缺失的最小基因值为1
        auto it = std::find(nums.begin(), nums.end(), 1);
        if (it == nums.end())   // 不存在基因值为1的节点
            return ans;

        // 建树
        std::vector<std::vector<int>> g(n);
        for (int i = 1; i < n; ++i)
            g[parents[i]].push_back(i);

        std::unordered_set<int> vis;
        std::stack<int> nodes;  // 保存接下来需要遍历的点
        int minMiss = 2, pre = -1, node = it - nums.begin();
        while (node >= 0)
        {
            vis.insert(nums[node]);
            for (int child : g[node])
            {
                if (child != pre)
                    nodes.push(child);
            }

            while (!nodes.empty())
            {
                int x = nodes.top();
                nodes.pop();
                vis.insert(nums[x]);
                for (int child : g[x])
                    nodes.push(child);
            }

            while (vis.find(minMiss) != vis.end())
                ++minMiss;

            ans[node] = minMiss;
            pre = node;
            node = parents[node];
        }

        return ans;
    }
};

class Solution3
{
public:
    std::vector<int> smallestMissingValueSubtree(std::vector<int> &parents, std::vector<int> &nums)
    {
        int n = parents.size();
        std::vector<int> ans(n, 1); // 子树中如果没有基因值为1的节点，则以i为根节点的子树缺失的最小基因值为1
        auto it = std::find(nums.begin(), nums.end(), 1);
        if (it == nums.end())   // 不存在基因值为1的节点
            return ans;

        // 建树
        std::vector<std::vector<int>> g(n);
        for (int i = 1; i < n; ++i)
            g[parents[i]].push_back(i);

        std::vector<bool> vis(n + 2, false);
        std::stack<int> nodes;  // 保存接下来需要遍历的点
        int minMiss = 2, pre = -1, node = it - nums.begin();
        while (node >= 0)
        {
            vis[std::min(nums[node], n + 1)] = true;
            for (int child : g[node])
            {
                if (child != pre)
                    nodes.push(child);
            }

            while (!nodes.empty())
            {
                int x = nodes.top();
                nodes.pop();
                vis[std::min(nums[x], n + 1)] = true;
                for (int child : g[x])
                    nodes.push(child);
            }

            while (vis[minMiss])
                ++minMiss;

            ans[node] = minMiss;
            pre = node;
            node = parents[node];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
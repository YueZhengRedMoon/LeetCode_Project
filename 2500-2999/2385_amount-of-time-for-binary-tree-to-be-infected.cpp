#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <algorithm>
#include "../leetcode.h"

class Solution
{
public:
    int amountOfTime(TreeNode* root, int startVal)
    {
        ans = 0;
        start = startVal;
        dfs(root);
        return ans;
    }

private:
    int ans;
    int start;

    // 如果返回值>=0，表示start在以root为根的树中，返回值为root到start的距离
    // 如果返回值<0，表示start不在以root为根的树中，返回值为root的深度
    int dfs(TreeNode* root)
    {
        int l = 0, r = 0;
        if (root->val == start) // 当前节点就是目标节点
        {
            if (root->left)
            {
                // 左孩子不为空时，递归求其深度（返回值是负数，深度为返回值的绝对值）
                l = dfs(root->left);
            }
            if (root->right)
            {
                // 右孩子不为空时，递归求其深度（返回值是负数，深度为返回值的绝对值）
                r = dfs(root->right);
            }
            ans = std::max({ans, -l, -r});
            // 返回当前节点到目标节点的距离 0
            return 0;
        }

        if (root->left)
        {
            l = dfs(root->left);
        }
        if (root->right)
        {
            r = dfs(root->right);
        }

        if (l > 0 || (l == 0 && root->left))    // start在左子树里
        {
            // 此时，以当前节点为根节点的整个子树里，距离start最远的节点可能在右子树里
            ans = std::max(ans, std::abs(r) + l + 1);
            return l + 1;
        }

        if (r > 0 || (r == 0 && root->right))   // start在右子树里
        {
            // 此时，以当前节点为根节点的整个子树里，距离start最远的节点可能在左子树里
            ans = std::max(ans, std::abs(l) + r + 1);
            return r + 1;
        }

        // start不在以当前节点为根的子树中，返回树的深度
        return std::min(l, r) - 1;
    }
};

class Solution2
{
public:
    int amountOfTime(TreeNode* root, int start)
    {
        // 建图
        std::unordered_map<int, std::vector<int>> g;
        std::function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int fa) -> void {
            std::vector<int>& neighbor = g[node->val];
            if (fa)
            {
                neighbor.push_back(fa);
            }
            if (node->left)
            {
                neighbor.push_back(node->left->val);
                dfs(node->left, node->val);
            }
            if (node->right)
            {
                neighbor.push_back(node->right->val);
                dfs(node->right, node->val);
            }
        };
        dfs(root, 0);

        std::unordered_set<int> infected;
        infected.insert(start);
        std::queue<std::pair<int, int>> q;
        q.emplace(start, 0);
        int infectedTime = 0;
        while (!q.empty())
        {
            int node = q.front().first;
            infectedTime = q.front().second;
            q.pop();

            for (int neighbor : g[node])
            {
                if (infected.find(neighbor) == infected.end())
                {
                    infected.insert(neighbor);
                    q.emplace(neighbor, infectedTime + 1);
                }
            }
        }

        return infectedTime;
    }
};

namespace WrongAnswer
{
    class Solution
    {
    public:
        int amountOfTime(TreeNode* root, int start)
        {
            startVal = start;
            maxDepthWithStart = 0;
            maxDepthWithoutStart = 0;

            dfs(root, 0, false);
            return std::max({startDepth, maxDepthWithStart - startDepth, startDepth + maxDepthWithoutStart});
        }

    private:
        int startDepth{0};
        int startVal{0};
        int maxDepthWithStart{0};
        int maxDepthWithoutStart{0};

        void dfs(TreeNode* node, int depth, bool passStart)
        {
            if (node->val == startVal)
            {
                passStart = true;
                startDepth = depth;
            }

            if (node->left == nullptr && node->right == nullptr)
            {
                if (passStart)
                {
                    if (depth > maxDepthWithStart)
                        maxDepthWithStart = depth;
                }
                else
                {
                    if (depth > maxDepthWithoutStart)
                        maxDepthWithoutStart = depth;
                }
                return;
            }

            if (node->left)
                dfs(node->left, depth + 1, passStart);
            if (node->right)
                dfs(node->right, depth + 1, passStart);
        }
    };

}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
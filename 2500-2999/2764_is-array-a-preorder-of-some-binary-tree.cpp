#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <unordered_map>

class Solution
{
public:
    bool isPreorder(std::vector<std::vector<int>>& nodes)
    {
        if (nodes[0][1] != -1)
            return false;

        int n = nodes.size();
        std::unordered_map<int, std::vector<int>> g(n);
        std::unordered_map<int, int> idx;    // id节点在nodes中的索引
        for (int i = 1; i < n; ++i)
        {
            int id = nodes[i][0], parentId = nodes[i][1];
            g[parentId].push_back(id);
            idx[id] = i;
        }

        // 当前访问的节点在nodes中的索引必须>leftStack栈顶节点在nodes中的索引
        // 当前访问的节点在nodes中的索引必须<rightStack栈顶节点在nodes中的索引
        std::stack<int> leftStack, rightStack;
        std::function<bool(int)> dfs = [&](int x) -> bool {
            if ((!leftStack.empty() && idx[x] < idx[leftStack.top()]) || (!rightStack.empty() && idx[x] > idx[rightStack.top()]))
                return false;

            bool res = false;
            leftStack.push(x);
            if (g[x].size() == 0)
            {
                res = true;
            }
            else if (g[x].size() == 1)
            {
                res = dfs(g[x][0]);
            }
            else    // g[x].size() == 2
            {
                int leftChild = g[x][0], rightChild = g[x][1];
                if (idx[leftChild] > idx[rightChild])
                    std::swap(leftChild, rightChild);
                rightStack.push(rightChild);
                res = dfs(leftChild);
                if (res)
                {
                    rightStack.pop();
                    res = dfs(rightChild);
                }
            }
            leftStack.pop();
            return res;
        };

        return dfs(nodes[0][0]);
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> nodes = {{0, -1}, {1, 0}, {2, 0}, {3, 2}, {4, 2}};
    bool ans = solution.isPreorder(nodes);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}

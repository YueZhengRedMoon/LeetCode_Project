#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>

class Solution
{
public:
    std::vector<int> sumOfDistancesInTree(int n, std::vector<std::vector<int>> &edges)
    {
        std::vector<int> ans(n, 0);
        std::vector<std::forward_list<int>> neighbor(n);
        std::vector<int> size(n, 1);    // 每棵子树的大小

        for (const std::vector<int> &edge : edges)
        {
            neighbor[edge[0]].emplace_front(edge[1]);
            neighbor[edge[1]].emplace_front(edge[0]);
        }

        std::function<void(int, int, int)> dfs = [&](int x, int par, int depth)
        {
            ans[0] += depth;
            for (int y : neighbor[x])
            {
                if (y != par)
                {
                    dfs(y, x, depth + 1);
                    size[x] += size[y];
                }
            }
        };
        dfs(0, -1, 0);

        std::function<void(int, int)> reRoot = [&](int x, int par)
        {
            for (int y : neighbor[x])
            {
                if (y != par)
                {
                    ans[y] = ans[x] + n - 2 * size[y];
                    reRoot(y, x);
                }
            }
        };
        reRoot(0, -1);

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

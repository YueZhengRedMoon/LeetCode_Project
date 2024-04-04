#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    std::vector<std::vector<int>> getAncestors(int n, std::vector<std::vector<int>>& edges)
    {

        std::vector<std::vector<bool>> reachable(n, std::vector<bool>(n));
        std::vector<std::vector<int>> g(n);
        std::vector<int> visit(n, -1);
        std::vector<int> reachCnt(n);
        for (const auto& edge : edges)
        {
            int x = edge[0], y = edge[1];
            g[y].push_back(x);
        }
        std::function<void(int, int)> dfs = [&](int x, int ancestor) -> void {
            visit[x] = ancestor;
            for (int y : g[x])
            {
                if (visit[y] != ancestor)
                {
                    reachable[ancestor][y] = true;
                    ++reachCnt[ancestor];
                    dfs(y, ancestor);
                }
            }
        };

        std::vector<std::vector<int>> ans(n);
        for (int i = 0; i < n; ++i)
        {
            dfs(i, i);
            ans.reserve(reachCnt[i]);
            for (int j = 0; j < n; ++j)
            {
                if (reachable[i][j])
                {
                    ans[i].push_back(j);
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

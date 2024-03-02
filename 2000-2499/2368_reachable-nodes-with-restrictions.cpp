#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    int reachableNodes(int n, std::vector<std::vector<int>>& edges, std::vector<int>& restricted)
    {
        std::unordered_set<int> restrictedSet(restricted.begin(), restricted.end());
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n - 1; ++i)
        {
            int x = edges[i][0], y = edges[i][1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = 0;
        std::function<void(int, int)> dfs = [&](int x, int fa) -> void {
            ++ans;
            for (int y : g[x])
            {
                if (y != fa && restrictedSet.find(y) == restrictedSet.end())
                {
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

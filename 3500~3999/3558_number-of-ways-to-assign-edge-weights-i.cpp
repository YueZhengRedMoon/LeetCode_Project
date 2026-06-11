#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int assignEdgeWeights(std::vector<std::vector<int>>& edges)
    {
        int n = edges.size() + 1;
        std::vector<std::vector<int>> g(n + 1);
        for (const std::vector<int>& e : edges)
        {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        std::function<int(int, int)> dfs = [&](int x, int fa) -> int {
            int maxDepth = 0;
            for (int y : g[x])
            {
                if (y != fa)
                {
                    int depth = dfs(y, x) + 1;
                    if (depth > maxDepth)
                        maxDepth = depth;
                }
            }
            return maxDepth;
        };
        int k = dfs(1, 0);

        return quickPowMod(2, k - 1);
    }

private:
    long long quickPowMod(long long x, long long n)
    {
        const int MOD = 1'000'000'007;
        long long res = 1;
        while (n)
        {
            if (n & 1)
                res = res * x % MOD;
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
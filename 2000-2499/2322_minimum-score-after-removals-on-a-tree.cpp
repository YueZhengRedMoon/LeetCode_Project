#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int minimumScore(std::vector<int>& nums, std::vector<std::vector<int>>& edges)
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

        std::vector<int> xr(n);     // xr[i]:以节点i为根的子树中所有节点值的异或和
        std::vector<int> in(n);     // in[i]:“递”到节点i的时间戳
        std::vector<int> out(n);    // out[i]:“归”到节点i的时间戳
        int clock = 0;              // 全局时间戳，每访问到一个新的节点便+1

        std::function<void(int, int)> dfs = [&](int x, int fa) -> void {
            in[x] = ++clock;    // 递
            xr[x] = nums[x];

            for (int y : g[x])
            {
                if (y != fa)
                {
                    dfs(y, x);
                    xr[x] ^= xr[y];
                }
            }

            out[x] = clock; // 归
        };
        dfs(0, -1);

        // 判断x是否为y的祖先
        auto isAncestor = [&](int x, int y) -> bool {
            return in[x] < in[y] && in[y] <= out[x];
        };

        int ans = INT_MAX;
        // 枚举：删除x与x父节点之间的边，删除y与y父节点之间的边
        for (int x = 2; x < n; ++x)
        {
            for (int y = 1; y < x; ++y)
            {
                int a, b, c;
                if (isAncestor(x, y))   // x是y的祖先
                {
                    a = xr[y];
                    b = xr[x] ^ a;
                    c = xr[0] ^ xr[x];
                }
                else if (isAncestor(y, x))  // y是x的祖先
                {
                    a = xr[x];
                    b = xr[y] ^ a;
                    c = xr[0] ^ xr[y];
                }
                else    // x和y分别属于两棵不相交的子树
                {
                    a = xr[x];
                    b = xr[y];
                    c = xr[0] ^ a ^ b;
                }

                ans = std::min(ans, std::max({a, b , c}) - std::min({a, b, c}));
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

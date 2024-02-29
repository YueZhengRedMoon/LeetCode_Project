#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    int rootCount(std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& guesses, int k)
    {
        std::vector<std::vector<int>> g(edges.size() + 1);
        for (auto& e : edges)
        {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        std::unordered_set<long long> s;    // guesses的哈希集合
        for (auto &e : guesses)
        {
            s.insert(hash(e[0], e[1]));
        }

        // dfs计算以0为根时的猜对次数
        int cnt0 = 0;
        std::function<void(int, int)> dfs = [&](int x, int fa) -> void {
            for (int y : g[x])
            {
                if (y != fa)
                {
                    cnt0 += s.count(hash(x, y));    // 以0为根时，猜对了
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        // 换根DP
        int ans = 0;
        std::function<void(int, int, int)> reRoot = [&](int x, int fa, int cnt) -> void {
            ans += cnt >= k;    // 此时cnt就是以x为根时的猜对次数
            for (int y : g[x])
            {
                if (y != fa)
                {
                    // 当树根由x变为y时，如果猜测有(x, y)则猜对次数-1，如果猜测有(y, x)则猜对次数+1
                    reRoot(y, x, cnt - s.count(hash(x, y)) + s.count(hash(y, x)));
                }
            }
        };
        reRoot(0, -1, cnt0);
        return ans;
    }

private:
    inline long long hash(int x, int y)
    {
        return ((long long) x << 32) | y;   // 两个 4 字节数压缩成一个 8 字节数
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

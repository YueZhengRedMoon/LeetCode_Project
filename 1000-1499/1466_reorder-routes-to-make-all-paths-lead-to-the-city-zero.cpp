#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int minReorder(int n, std::vector<std::vector<int>> &connections)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto &connection : connections)
        {
            int a = connection[0], b = connection[1];
            graph[a].push_back(b * 10 + 1);
            graph[b].push_back(a * 10);
        }

        int ans = 0;
        std::function<void(int, int)> dfs = [&](int x, int fa) {
            for (int y : graph[x])
            {
                int city = y / 10;
                if (city != fa)
                {
                    ans += y & 1;
                    dfs(city, x);
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

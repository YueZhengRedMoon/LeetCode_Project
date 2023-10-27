#include <iostream>
#include <vector>
#include <functional>
#include <cstring>

constexpr int MAX_N = 100001;
bool isPrime[MAX_N];
int init = [](){
    std::memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAX_N; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i + i; j < MAX_N; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return 0;
}();

class Solution
{
public:
    long long countPaths(int n, std::vector<std::vector<int>> &edges)
    {
        std::vector<std::vector<int>> graph(n + 1);
        for (const std::vector<int> &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // 计算从i号节点出发，经过的合法路径的数量
        std::vector<long long> validPathNums(n + 1, 0);
        std::function<void(int, int, std::vector<int> &)>
        dfs = [&](int cur, int par, std::vector<int> &visited) -> void {
            visited.push_back(cur);
            for (int next : graph[cur])
            {
                if (!isPrime[next] && next != par)
                {
                    dfs(next, cur, visited);
                }
            }
        };

        long long ans = 0;
        for (int u = 1; u <= n; ++u)
        {
            if (!isPrime[u])
                continue;

            long long sum = 0;
            for (int v : graph[u])
            {
                if (isPrime[v])
                    continue;

                if (validPathNums[v] == 0)
                {
                    std::vector<int> visited;
                    dfs(v, 0, visited);
                    long long num = visited.size();
                    for (int x : visited)
                        validPathNums[x] = num;
                }
                ans += validPathNums[v] * sum;
                sum += validPathNums[v];
            }
            ans += sum;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

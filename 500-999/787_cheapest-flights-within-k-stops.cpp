#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <unordered_map>

class Solution
{
public:
    struct OutEdge
    {
        int to;
        int cost;
    };

    struct Status
    {
        int minCost;
        int minStops;
        int id;

        Status(int cost = 0, int stops = 0, int cityID = 0)
        : minCost(cost), minStops(stops), id(cityID) {}

        bool operator > (const Status &rhs) const
        {
            if (minCost == rhs.minCost)
            {
                return minStops > rhs.minStops;
            }
            return minCost > rhs.minCost;
        }
    };

    int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src, int dst, int k)
    {
        std::vector<std::forward_list<OutEdge>> adjList(n);
        for (const auto &flight : flights)
        {
            adjList[flight[0]].push_front({flight[1], flight[2]});
        }

        const int inf = 0x3f3f3f3f;
        std::vector<std::unordered_map<int, int>> dis(n);
        std::priority_queue<Status, std::vector<Status>, std::greater<>> queue;

        dis[src][-1] = 0;
        queue.emplace(0, -1, src);
        while (!queue.empty())
        {
            Status top = queue.top();
            queue.pop();
            if (top.minStops >= k || (dis[top.id].find(top.minStops) != dis[top.id].end()
                && top.minCost > dis[top.id][top.minStops]))
                continue;
            for (const auto &e : adjList[top.id])
            {
                int newCost = top.minCost + e.cost;
                int newStops = top.minStops + 1;
                auto it = dis[e.to].find(newStops);
                if (it == dis[e.to].end())
                {
                    dis[e.to][newStops] = newCost;
                    queue.emplace(newCost, newStops, e.to);
                }
                else if (newCost < it->second)
                {
                    it->second = newCost;
                    queue.emplace(newCost, newStops, e.to);
                }
            }
        }

        int ans = inf;
        for (auto [stop, cost] : dis[dst])
        {
            if (cost < ans)
            {
                ans = cost;
            }
        }
        return ans == inf ? -1 : ans;
    }
};

class Solution2
{
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src, int dst, int k)
    {
        const int inf = 0x3f3f3f3f;
        // dp[i][j]:经过i次中转从src到达dst的最小成本
        std::vector<std::vector<int>> dp(2, std::vector<int>(n, inf));
        dp[0][src] = 0;

        int ans = inf, flightsNum = flights.size();
        for (int i = 1; i <= k + 1; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            std::fill(dp[cur].begin(), dp[cur].end(), inf);
            for (int j = 0; j < flightsNum; ++j)
            {
                int from = flights[j][0];
                if (dp[last][from] != inf)
                {
                    int to = flights[j][1], cost = flights[j][2];
                    dp[cur][to] = std::min(dp[cur][to], dp[last][from] + cost);
                    if (to == dst && dp[cur][to] < ans)
                    {
                        ans = dp[cur][to];
                    }
                }
            }
        }

        return ans == inf ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
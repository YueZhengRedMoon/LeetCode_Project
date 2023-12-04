#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    long long minimumFuelCost(std::vector<std::vector<int>> &roads, int seats)
    {
        long long ans = 0;
        int n = roads.size() + 1;

        std::vector<std::vector<int>> graph(n);
        for (auto &road : roads)
        {
            int a = road[0], b = road[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        std::function<int(int, int)> dfs = [&](int x, int fa) -> int {
            int size = 1;
            for (int y : graph[x])
            {
                if (y != fa)
                {
                    size += dfs(y, x);
                }
            }
            if (x)
            {
                ans += (size - 1) / seats + 1;  // ceil(a/b) = (a - 1) / b + 1
            }
            return size;
        };
        dfs(0, -1);

        return ans;
    }
};

namespace ErrorSolution
{
    class Solution
    {
    public:
        long long minimumFuelCost(std::vector<std::vector<int>> &roads, int seats)
        {
            long long ans = 0;
            int n = roads.size() + 1;

            std::vector<std::vector<int>> graph(n);
            for (auto &road : roads)
            {
                int a = road[0], b = road[1];
                graph[a].push_back(b);
                graph[b].push_back(a);
            }

            // return: first:leftSeats, second:vehicleCount
            std::function<std::pair<int, int>(int, int)> dfs = [&](int city, int from) -> std::pair<int, int> {
                int leftSeats = 0, vehicleCount = 0;
                for (int nextCity : graph[city])
                {
                    if (nextCity != from)
                    {
                        auto res = dfs(nextCity, city);
                        leftSeats += res.first;
                        vehicleCount += res.second;
                    }
                }

                ans += vehicleCount;
                if (leftSeats == 0)
                {
                    leftSeats = seats - 1;
                    ++vehicleCount;
                }
                else
                {
                    --leftSeats;
                }

                return {leftSeats, vehicleCount};
            };

            dfs(0, -1);

            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <functional>
#include <queue>

class Solution
{
public:
    using Pair = std::pair<int, int>;

    std::vector<int> assignBikes(std::vector<std::vector<int>> &workers, std::vector<std::vector<int>> &bikes)
    {
        int n = workers.size(), m = bikes.size();
        std::vector<bool> workerAllocated(n, false), bikeAllocated(m, false);
        std::vector<int> ans(n);

        auto manhattan = [&](int w, int b) {
            return std::abs(workers[w][0] - bikes[b][0]) + std::abs(workers[w][1] - bikes[b][1]);
        };

        std::priority_queue<Pair, std::vector<Pair>, std::function<bool(const Pair&, const Pair&)>>
        minHeap([&](const Pair &lhs, const Pair &rhs) -> bool {
            int dis1 = manhattan(lhs.first, lhs.second);
            int dis2 = manhattan(rhs.first, rhs.second);
            if (dis1 == dis2)
            {
                if (lhs.first == rhs.first)
                    return lhs.second > rhs.second;
                return lhs.first > rhs.first;
            }
            return dis1 > dis2;
        });

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                minHeap.emplace(i, j);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            while (!minHeap.empty())
            {
                auto [w, b] = minHeap.top();
                minHeap.pop();
                if (!workerAllocated[w] && !bikeAllocated[b])
                {
                    ans[w] = b;
                    workerAllocated[w] = true;
                    bikeAllocated[b] = true;
                    break;
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

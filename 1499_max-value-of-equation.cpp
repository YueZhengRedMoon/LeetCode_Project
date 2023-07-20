#include <iostream>
#include <vector>
#include <limits>
#include <queue>

class Solution
{
public:
    using Pair = std::pair<int, int>;

    int findMaxValueOfEquation(std::vector<std::vector<int>> &points, int k)
    {
        int ans = std::numeric_limits<int>::min();
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> minHeap;
        for (const std::vector<int> &point : points)
        {
            int x = point[0], y = point[1];
            while (!minHeap.empty() && x - minHeap.top().second > k)
            {
                minHeap.pop();
            }
            if (!minHeap.empty())
            {
                ans = std::max(ans, x + y - minHeap.top().first);
            }
            minHeap.emplace(x - y, x);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
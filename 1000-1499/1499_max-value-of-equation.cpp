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

class Solution2
{
public:
    using Pair = std::pair<int, int>;

    int findMaxValueOfEquation(std::vector<std::vector<int>> &points, int k)
    {
        // xj > xi -> yi + yj + |xi - xj| = xj + yj - xi + yi = xj + yj + yi - xi
        int ans = std::numeric_limits<int>::min();
        std::deque<Pair> deque;
        for (const std::vector<int> &point : points)
        {
            int x = point[0], y = point[1];
            while (!deque.empty() && x - deque.front().second > k)   // xj - xi > k
            {
                deque.pop_front();
            }
            if (!deque.empty())
            {
                ans = std::max(ans, x + y + deque.front().first);   // xj + yj + yi - xi
            }
            while (!deque.empty() && y - x >= deque.back().first)
            {
                deque.pop_back();
            }
            deque.emplace_back(y - x, x);   // yi - xi, xi
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

class Solution
{
public:
    int minDays(int n)
    {
        if (n <= 1)
            return n;
        if (memo.find(n) != memo.end())
            return memo[n];

        return memo[n] = std::min(minDays(n / 2) + n % 2, minDays(n / 3) + n % 3) + 1;
    }

private:
    std::unordered_map<int, int> memo;
};

class Solution2
{
public:
    int minDays(int n)
    {
        std::unordered_map<int, int> dis;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.emplace(0, n);
        while (true)
        {
            auto [dx, x] = pq.top();
            pq.pop();
            if (x <= 1)
                return dx + x;
            if (dx > dis[x])
                continue;
            for (int d = 2; d <= 3; ++d)
            {
                int y = x / d;
                int dy = dx + x % d + 1;
                if (dis.find(y) == dis.end() || dy < dis[y])
                {
                    dis[y] = dy;
                    pq.emplace(dy, y);
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

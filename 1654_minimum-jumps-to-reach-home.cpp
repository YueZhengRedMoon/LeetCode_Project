#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

// 错误
class Solution
{
public:
    int minimumJumps(std::vector<int> &forbidden, int a, int b, int x)
    {
        // 由于不能连续向后跳2次，所以每次向后跳的前一次必须是向前跳
        // 因此对与向后跳，可以等价于向前跳(c=a-b)，如果(a-b<0)则是向后跳

        // 起点就是家，无需跳跃
        if (x == 0)
            return 0;

        std::unordered_set<int> forbidSet(forbidden.begin(), forbidden.end());
        const int inf = 0x3f3f3f3f;
        int farthest = x + a + 1;
        std::vector<int> dp(farthest, inf);
        dp[0] = 0;
        int c = a - b;

        auto calcDp = [&](int begin, int end, int delta){
            for (int i = begin; i != end; i += delta)
            {
                // 当前区域禁止跳跃
                if (forbidSet.find(i) != forbidSet.end())
                    continue;

                if (i - a >= 0 && forbidSet.find(i - a) == forbidSet.end())
                {
                    dp[i] = std::min(dp[i], dp[i - a] + 1);
                }
                if (i - c >= 0 && i - c < farthest && forbidSet.find(i - c) == forbidSet.end())
                {
                    dp[i] = std::min(dp[i], dp[i - c] + 2);
                }
            }
            return dp[x];
        };

        int last = calcDp(1, farthest, 1);
        if (c < 0)
        {
            while (calcDp(1, farthest, 1) != last)
            {
                last = dp[x];
            }
        }

        return dp[x] == inf ? -1 : dp[x];
    }
};

// 错误
class Solution2
{
public:
    int minimumJumps(std::vector<int> &forbidden, int a, int b, int x)
    {
        // 可以证明，一定可以在max(f+a+b,x+b)的范围中找到最优解，其中f是最远的禁止点的坐标

        int f = 0;
        std::unordered_set<int> ban;
        ban.reserve(forbidden.size());
        for (int forbid : forbidden)
        {
            ban.insert(forbid);
            if (forbid > f)
                f = forbid;
        }

        const int inf = 0x3f3f3f3f;
        int c = a - b;
        int bound = std::max(f + a + b, x + b);
        std::vector<int> dist(bound, inf);
        dist[0] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
        queue.emplace(0, 0);

        while (!queue.empty())
        {
            auto [d, i] = queue.top();
            queue.pop();

            if (d > dist[i])
                continue;

            int next = i + a;
            int nextDis = d + 1;
            if (next < bound && ban.find(next) == ban.end() && nextDis < dist[next])
            {
                dist[next] = nextDis;
                queue.emplace(nextDis, next);
            }

            next = i + c;
            nextDis = d + 2;
            if (next > 0 && next < bound && ban.find(next) == ban.end() && nextDis < dist[next])
            {
                dist[next] = nextDis;
                queue.emplace(nextDis, next);
            }
        }

        return dist[x] == inf ? -1 : dist[x];
    }
};

class Solution3
{
public:
    int minimumJumps(std::vector<int> &forbidden, int a, int b, int x)
    {
        // 可以证明，一定可以在max(f+a+b,x+b)的范围中找到最优解，其中f是最远的禁止点的坐标

        int f = 0;
        std::unordered_set<int> ban;
        ban.reserve(forbidden.size());
        for (int forbid : forbidden)
        {
            ban.insert(forbid);
            if (forbid > f)
                f = forbid;
        }

        const int inf = 0x3f3f3f3f;
        int bound = std::max(f + a + b, x + b);
        // dist[i][0]:上一次前跳，dist[i][1]:上一次后跳
        std::vector<std::vector<int>> dist(bound + 1, std::vector<int>(2, inf));
        dist[0][0] = 0;
        std::queue<std::pair<int, int>> queue({{0, 0}});
        while (!queue.empty())
        {
            auto [i, pre] = queue.front();
            queue.pop();

            if (i == x)
                return dist[i][pre];

            // 后跳
            if (pre == 0 && i - b >= 0 && ban.find(i - b) == ban.end() && dist[i][pre] + 1 < dist[i - b][1])
            {
                dist[i - b][1] = dist[i][pre] + 1;
                queue.emplace(i - b, 1);
            }

            // 前跳
            if (i + a <= bound && ban.find(i + a) == ban.end() && dist[i][pre] + 1 < dist[i + a][0])
            {
                dist[i + a][0] = dist[i][pre] + 1;
                queue.emplace(i + a, 0);
            }
        }

        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

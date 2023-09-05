#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int maximumInvitations(std::vector<int> &favorite)
    {
        int n = favorite.size();
        std::vector<int> inDeg(n, 0);
        for (int v : favorite)
        {
            ++inDeg[v];
        }

        std::queue<std::pair<int, int>> queue;    // first:from, second:to
        for (int i = 0; i < n; ++i)
        {
            if (inDeg[i] == 0)
                queue.emplace(i, favorite[i]);
        }

        std::vector<int> dis(n, 0); // dis[i]:从入度为0的顶点到达i最多经过几个顶点
        while (!queue.empty())
        {
            auto [from, to] = queue.front();
            queue.pop();

            dis[to] = std::max(dis[to], dis[from] + 1);
            if (--inDeg[to] == 0)
            {
                queue.emplace(to, favorite[to]);
            }
        }

        int ans = 0;
        int pairSum = 0;
        for (int i = 0; i < n; ++i)
        {
            if (inDeg[i] != 0)
            {
                int ringLen = 1;
                int x = favorite[i];
                while (x != i)
                {
                    inDeg[x] = 0;
                    x = favorite[x];
                    ++ringLen;
                }
                if (ringLen == 2)
                {
                    int pair = ringLen + dis[i] + dis[favorite[i]];
                    ans = std::max(ans, pair);
                    pairSum += pair;
                }
                else
                    ans = std::max(ans, ringLen);
            }
        }

        return std::max(ans, pairSum);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

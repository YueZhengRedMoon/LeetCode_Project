#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfSets(int n, int maxDistance, std::vector<std::vector<int>>& roads)
    {
        const int inf = 0x3f3f3f3f;
        std::vector<std::vector<int>> dis(n, std::vector<int>(n, inf));
        for (int i = 0; i < n; ++i)
            dis[i][i] = 0;
        for (const std::vector<int>& road : roads)
        {
            int u = road[0], v = road[1], w = road[2];
            if (dis[u][v] > w)
            {
                dis[u][v] = w;
                dis[v][u] = w;
            }
        }

        int ans = 1;
        for (int s = 1; s < (1 << n); ++s)
        {
            int res = check(s, dis, maxDistance);
            ans += res;
        }
        return ans;
    }

private:
    int check(int s, std::vector<std::vector<int>> dis, int maxDis)
    {
        std::vector<int> branches;
        for (int i = 0, tmp = s; tmp; ++i, tmp >>= 1)
        {
            // s第i位=1表示保留第i个分部
            if (tmp & 1)
            {
                branches.push_back(i);
            }
        }

        // Floyd算法
        for (int k : branches)
        {
            for (int i : branches)
            {
                for (int j : branches)
                {
                    dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        for (int i = 0; i < branches.size(); ++i)
        {
            for (int j = i + 1; j < branches.size(); ++j)
            {
                if (dis[branches[i]][branches[j]] > maxDis)
                    return 0;
            }
        }
        return 1;
    }
};

int main()
{
    Solution solution;
    int n = 3;
    int maxDis = 12;
    std::vector<std::vector<int>> roads = {{1, 0, 11}, {1, 0, 16}, {0, 2, 13}};
    int ans = solution.numberOfSets(n, maxDis, roads);
    std::cout << ans << std::endl;
    return 0;
}

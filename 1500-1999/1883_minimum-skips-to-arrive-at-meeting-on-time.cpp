#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

class Solution
{
public:
    int minSkips(std::vector<int>& dist, int speed, int hoursBefore)
    {
        if (std::accumulate(dist.begin(), dist.end(), 0) > (long long) speed * hoursBefore)
            return -1;

        int n = dist.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1)); // -1表示没有计算过
        // dfs(i, j)：在最多跳过i次的情况下，从dist[0]到dist[j]需要的最小时间
        // 如果在j处选择不跳过，则dfs(i, j)包含了在j处等待的时间
        std::function<int(int ,int)> dfs = [&](int i, int j) -> int {
            if (j < 0)  // 递归边界
                return 0;

            int& res = memo[i][j];
            if (res != -1)
                return res;

            res = ((dfs(i, j - 1) + dist[j] + speed - 1) / speed) * speed;  // 在j处选择不跳过
            if (i)
                res = std::min(res, dfs(i - 1, j - 1) + dist[j]);   // 在j处选择跳过

            return res;
        };

        for (int i = 0;; ++i)
        {
            // 在n-1处不用跳过
            if (dfs(i, n - 2) + dist[n - 1] <= (long long) speed * hoursBefore)
                return i;
        }
    }
};

class Solution2
{
public:
    int minSkips(std::vector<int>& dist, int speed, int hoursBefore)
    {
        long long totalDist = (long long) speed * hoursBefore;
        if (std::accumulate(dist.begin(), dist.end(), 0) > totalDist)
            return -1;

        int n = dist.size();
        // f[i][j]:在最多跳过i次的情况下从dist[0]到dist[j]等价走过的最短路径长度
        std::vector<std::vector<int>> f(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                f[i][j] = (f[i][j - 1] + dist[j - 1] + speed - 1) / speed * speed;  // 在j处选择不跳过
                if (i)
                {
                    f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + dist[j - 1]); // 在j处选择跳过
                }
            }
        }
        totalDist -= dist[n - 1];
        for (int i = 0; i < n; ++i)
        {
            if (f[i][n - 1] <= totalDist)
                return i;
        }
        return -1;
    }
};

class Solution3
{
public:
    int minSkips(std::vector<int>& dist, int speed, int hoursBefore)
    {
        long long totalDist = (long long) speed * hoursBefore;
        if (std::accumulate(dist.begin(), dist.end(), 0) > totalDist)
            return -1;

        int n = dist.size();
        // f[i][j]:在最多跳过j次的情况下从dist[0]到dist[i]等价走过的最短路径长度
        std::vector<std::vector<int>> f(2, std::vector<int>(n, 0));
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int cur = i % 2, last = (i - 1) % 2;
                f[cur][j] = (f[last][j] + dist[i - 1] + speed - 1) / speed * speed;  // 在i处选择不跳过
                if (j)
                {
                    f[cur][j] = std::min(f[cur][j], f[last][j - 1] + dist[i - 1]); // 在i处选择跳过
                }
            }
        }
        totalDist -= dist[n - 1];
        int end = (n - 1) % 2;
        for (int j = 0; j < n; ++j)
        {
            if (f[end][j] <= totalDist)
                return j;
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

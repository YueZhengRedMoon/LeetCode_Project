#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Solution
{
public:
    double minmaxGasDist(std::vector<int>& stations, int k)
    {
        int n = stations.size();
        std::vector<double> dis(n - 1);
        for (int i = 1; i < n; ++i)
        {
            dis[i - 1] = stations[i] - stations[i - 1];
        }
        std::sort(dis.rbegin(), dis.rend());

        double left = 0.0, right = dis[0], ans = dis[0];
        while (right - left > 1e-6)
        {
            double mid = (left + right) / 2.0;
            if (check(dis, k, mid)) // 可以在增加k个加油站后使相邻加油站的最大距离<=mid
            {
                ans = mid;
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        return ans;
    }

private:
    // 检查是否可以通过增加k个加油站使相邻两个加油站的最大距离<=maxDis
    bool check(const std::vector<double>& dis, int k, double maxDis)
    {
        for (double d : dis)
        {
            if (d < maxDis)
                return true;
            int cnt = (int) std::ceil(d / maxDis) - 1; // 需要增加cnt个加油站才能使这段距离中相邻加油站的距离<=maxDis
            if (cnt <= k)
                k -= cnt;
            else
                return false;
        }
        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<int> stations = {23,24,36,39,46,56,57,65,84,98};
    int k = 1;
    double ans = solution.minmaxGasDist(stations, k);
    std::cout << ans << std::endl;
    return 0;
}

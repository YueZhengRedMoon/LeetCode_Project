#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <execution>

class Solution
{
public:
    int minSpeedOnTime(std::vector<int>& dist, double hour)
    {
        int n = dist.size();
        // hour最多有2位小数，规避浮点数；
        // 双精度浮点数无法准确表示2.01这样的小数，计算2.01*100时，算出的结果不是201，而是200.999...这样的数，需要四舍五入
        long long h100 = std::round(hour * 100);
        // 每趟车至少需要耗费1小时，如果hour <= n-1，则不可能准时到达（还有一躺车来不及乘）
        long long delta = h100 - (n - 1) * 100;
        if (delta <= 0)
            return -1;

        int maxDist = *std::max_element(dist.begin(), dist.end());
        if (h100 <= n * 100)
        {
            return std::max(maxDist, (int) ((dist.back() * 100 - 1) / delta + 1));
        }

        auto check = [&](int v) -> bool
        {
            long long t = 0;
            for (int i = 0; i < n - 1; ++i)
            {
                t += (dist[i] - 1) / v + 1;
            }
            return (t * v + dist.back()) * 100 <= h100 * v;
        };

        long long sumDist = std::reduce(dist.begin(), dist.end(), 0ll);
        int left = (sumDist * 100 - 1) / h100;
        int h = h100 / (n * 100);
        int right = (maxDist - 1) / h + 1;
        while (left + 1 < right)
        {
            int mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};

int main()
{
    Solution solution;
    std::vector<int> dist = {1,1,100000};
    double hour = 2.01;
    int ans = solution.minSpeedOnTime(dist, hour);
    std::cout << ans << std::endl;
    return 0;
}

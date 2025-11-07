#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxPower(std::vector<int>& stations, int r, int k)
    {
        int n = stations.size();
        std::vector<long long> diff(n + 1);
        for (int i = 0; i < n; ++i)
        {
            diffAdd(diff, i - r, i + r, stations[i]);
        }

        long long power = 0, minPower = diff[0];
        for (int i = 0; i < n; ++i)
        {
            power += diff[i];
            if (power < minPower)
                minPower = power;
        }

        long long left = minPower + k / n, right = minPower + k + 1;
        long long ans = 0;
        while (left < right)
        {
            long long mid = left + (right - left) / 2;
            if (check(diff, k, r, mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return ans;
    }

private:
    // 通过差分数组，将区间[begin, end]中的值加val，同时避免索引越界
    void diffAdd(std::vector<long long>& diff, int begin, int end, long long val)
    {
        begin = std::max(begin, 0);
        end = std::min(end + 1, (int) diff.size() - 1);
        diff[begin] += val;
        diff[end] -= val;
    }

    // 检查通过增加k座供电站，是否可以使每座城市的电量都>=minPower
    bool check(std::vector<long long> diff, long long k, int r, long long minPower)
    {
        long long sum = 0;  // 前缀和
        int n = (int) diff.size() - 1;
        for (int i = 0; i < n && k >= 0; ++i)   // 遍历到第i座城市时的sum既为第i座城市的电量
        {
            sum += diff[i];
            if (sum < minPower)
            {
                long long delta = minPower - sum;
                diffAdd(diff, i, i + 2 * r, delta);
                sum += delta;
                k -= delta;
            }
        }
        return k >= 0;
    }
};

int main()
{
    Solution solution;
    std::vector<int> stations = {1, 2, 4, 5, 0};
    int r = 1;
    int k = 2;
    long long ans = solution.maxPower(stations, r, k);
    std::cout << ans << std::endl;
    return 0;
}
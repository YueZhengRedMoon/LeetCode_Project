#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

class Solution
{
public:
    long long minNumberOfSeconds(int mountainHeight, std::vector<int>& workerTimes)
    {
        long long maxTime = *std::max_element(workerTimes.begin(), workerTimes.end());
        maxTime *= (1ll + mountainHeight) * mountainHeight / 2ll;

        // 检查所有工人工作不超过t秒，是否可以使山的高度降低到 0
        auto check = [&](long long t) -> bool {
            long long height = mountainHeight;
            for (long long y : workerTimes)
            {
                if (height <= 0)
                {
                    break;
                }

                long long k = t / y;
                long long x = (long long) std::floor((-1 + std::sqrt(1 + 8 * k)) / 2);
                height -= x;
            }
            return height <= 0;
        };

        long long left = 0, right = maxTime + 1, ans = 0;
        while (left < right)
        {
            long long mid = left + (right - left) / 2ll;
            if (check(mid)) // 所有工人工作不超过mid秒，可以使山的高度降低为0
            {
                ans = mid;
                right = mid;
            }
            else    // 所有工人至多工作mid秒，无法使山的高度降低为0，需要更多的时间
            {
                left = mid + 1;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    using Tuple3 = std::tuple<long long, long long, int>;

    long long minNumberOfSeconds(int mountainHeight, std::vector<int>& workerTimes)
    {
        std::priority_queue<Tuple3, std::vector<Tuple3>, std::greater<>> pq;    // 小顶堆
        for (int t : workerTimes)
        {
            pq.emplace(t, t, t);
        }
        long long ans = 0;
        while (mountainHeight--)
        {
            // 工作后总用时，当前工作（山高度降低 1）用时，workerTimes[i]
            auto [total, cur, base] = pq.top();
            pq.pop();
            ans = total;
            pq.emplace(total + cur + base, cur + base, base);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
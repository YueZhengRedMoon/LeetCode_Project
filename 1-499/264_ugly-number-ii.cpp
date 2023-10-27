#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/** 超时 */
class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 6)
        {
            return n;
        }
        std::vector<bool> isUgly(7, true);
        isUgly.reserve(n * 5);

        int count = 6, i, result;
        for (i = 7; count < n; ++i)
        {
            if ((i % 2 == 0 && isUgly[i / 2]) ||
                (i % 3 == 0 && isUgly[i / 3]) ||
                (i % 5 == 0 && isUgly[i / 5]))
            {
                isUgly.push_back(true);
                ++count;
                result = i;
            }
            else
            {
                isUgly.push_back(false);
            }
        }

        return result;
    }
};

/** 最小堆 */
class Solution2
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 6)
        {
            return n;
        }

        int factors[] = {2, 3, 5};
        std::priority_queue<long long, std::vector<long long>, std::greater<> > heap;
        std::unordered_set<long long> seen;
        heap.push(1ll);
        seen.insert(1ll);
        long long ugly = 0;
        for (int i = 0; i < n; ++i)
        {
            ugly = heap.top();
            heap.pop();

            for (int factor : factors)
            {
                if (seen.insert(ugly * factor).second)
                {
                    heap.push(ugly * factor);
                }
            }
        }

        return static_cast<int>(ugly);
    }
};

class Solution3
{
public:
    int nthUglyNumber(int n)
    {
        std::vector<int> dp(n + 1);
        dp[1] = 1;

        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; ++i)
        {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = std::min(std::min(num2, num3), num5);
            if (dp[i] == num2)
            {
                // dp[p2] * 2 == dp[i] --> dp[p2+1] * 2 >= dp[i+1]
                ++p2;
            }
            if (dp[i] == num3)
            {
                // dp[p3] * 3 == dp[3] --> dp[p3+1] * 3 >= dp[i+1]
                ++p3;
            }
            if (dp[i] == num5)
            {
                // dp[p5] * 5 == dp[5] --> dp[p5+1] * 5 >= dp[i+1]
                ++p5;
            }
        }

        return dp[n];
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution2 solution;
    int result = solution.nthUglyNumber(n);
    std::cout << result << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        int n = days.size(), c1 = costs[0], c7 = costs[1], c30 = costs[2];
        int minCost = std::min({c1, c7, c30});
        std::vector<int> f(n + 1);  // f[i]:完成days[0, i)所需的最低消费
        for (int i = 1; i <= n; ++i)
        {
            f[i] = f[i - 1] + minCost;
            for (int j = i - 2; j >= 0; --j)
            {
                int delta = days[i - 1] - days[j] + 1;
                if (delta > 30)
                    break;

                f[i] = std::min(f[i], f[j] + c30);
                if (delta <= 7)
                    f[i] = std::min(f[i], f[j] + c7);
            }
        }
        return f[n];
    }
};

class Solution2
{
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        int n = days.size();
        std::vector<int> f(n + 1);
        int j = 0, k = 0;
        for (int i = 0; i < n; ++i)
        {
            int d = days[i];
            while (days[j] <= d - 7)
                ++j;
            while (days[k] <= d - 30)
                ++k;
            f[i + 1] = std::min({f[i] + costs[0], f[j] + costs[1], f[k] + costs[2]});
        }
        return f[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int maxSatisfied(std::vector<int>& customers, std::vector<int>& grumpy, int minutes)
    {
        int n = customers.size();
        std::vector<int> prefix1(n + 1, 0);     // customers的前缀和数组
        std::vector<int> prefix2(n + 1, 0);     // 老板生气时的customers前缀和数组
        for (int i = 0; i < n; ++i)
        {
            prefix1[i + 1] = prefix1[i] + customers[i];
            prefix2[i + 1] = prefix2[i] + (grumpy[i] ? 0 : customers[i]);
        }

        // 计算区间[i, j]之间的元素和
        // prefix[i]=a[0]+a[1]+...+a[i-1]
        auto sum = [](const std::vector<int>& prefix, int i, int j) -> int {
            if (i > j)
                return 0;
            return prefix[j + 1] - prefix[i];
        };

        int ans = 0;
        for (int end = minutes - 1; end < n; ++end)   // 枚举结束冷静的时间
        {
            int begin = end - minutes + 1;  // 开始冷静的时间
            ans = std::max(ans, sum(prefix2, 0, begin - 1) + sum(prefix1, begin, end) + sum(prefix2, end + 1, n - 1));
        }

        return ans;
    }
};

class Solution2
{
public:
    int maxSatisfied(std::vector<int>& customers, std::vector<int>& grumpy, int minutes)
    {
        int n = customers.size();
        int satisfaction = std::accumulate(customers.begin(), customers.begin() + minutes, 0);  // 满意的人数
        for (int i = minutes; i < n; ++i)
        {
            if (!grumpy[i])
                satisfaction += customers[i];
        }

        int ans = satisfaction;
        for (int i = 0, j = minutes; j < n; ++i, ++j)
        {
            if (grumpy[j])
                satisfaction += customers[j];
            if (grumpy[i])
                satisfaction -= customers[i];
            if (satisfaction > ans)
                ans = satisfaction;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> customers = {1,0,1,2,1,1,7,5};
    std::vector<int> grumpy = {0,1,0,1,0,1,0,1};
    int minutes = 3;
    int ans = solution.maxSatisfied(customers, grumpy, minutes);
    std::cout << ans << std::endl;
    return 0;
}

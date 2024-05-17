#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    int maxProfitAssignment(std::vector<int>& difficulty, std::vector<int>& profit, std::vector<int>& worker)
    {
        int n = difficulty.size();
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        // 按照工作难度升序排序
        std::sort(idx.begin(), idx.end(), [&](int i, int j) {return difficulty[i] < difficulty[j];});

        // maxProfit[i]:idx[0,i]中最大的profit
        std::vector<int> maxProfit(n);
        maxProfit[0] = profit[idx[0]];
        for (int i = 1; i < n; ++i)
        {
            maxProfit[i] = std::max(maxProfit[i - 1], profit[idx[i]]);
        }

        int ans = 0;
        for (int w : worker)
        {
            // 找到第一个工作难度大于能力w的工作的索引
            int left = 0, right = n, res = n;
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (difficulty[idx[mid]] > w)
                {
                    res = mid;
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            if (res > 0)
            {
                ans += maxProfit[res - 1];
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

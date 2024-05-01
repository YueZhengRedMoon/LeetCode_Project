#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

class Solution
{
public:
    double mincostToHireWorkers(std::vector<int>& quality, std::vector<int>& wage, int k)
    {
        int n = quality.size(), sumQ = 0;
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        // 按照r=wage/quality从小到大排序
        std::sort(idx.begin(), idx.end(), [&](int i, int j) -> bool {return wage[i] * quality[j] < quality[i] * wage[j];});

        std::priority_queue<int> pq;    // 大顶堆
        for (int i = 0; i < k; ++i)
        {
            pq.push(quality[idx[i]]);
            sumQ += quality[idx[i]];
        }
        double ans = sumQ * ((double) wage[idx[k - 1]] / quality[idx[k - 1]]);  // 选r值最小的
        for (int i = k; i < n; ++i)
        {
            if (int q = quality[idx[i]]; q < pq.top())  // sumQ可以变小，从而可能得到更优的答案
            {
                sumQ -= pq.top() - q;
                pq.pop();
                pq.push(q);
                ans = std::min(ans, sumQ * ((double) wage[idx[i]] / q));
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

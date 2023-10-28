#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> minInterval(std::vector<std::vector<int>> &intervals, std::vector<int> &queries)
    {
        // 按照区间长度由小到大排序，这样每次回答的时候用的就是长度最小的区间
        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int> &lhs, const std::vector<int> &rhs)
                  {
                      return (lhs[1] - lhs[0]) < (rhs[1] - rhs[0]);
                  });

        int m = queries.size();
        std::vector<std::pair<int, int>> qs(m);
        for (int i = 0; i < m; ++i)
        {
            qs[i].first = queries[i];
            qs[i].second = i;
        }
        // 离线，按查询位置排序
        std::sort(qs.begin(), qs.end());

        // 初始化并查集
        parent.resize(m + 1);
        std::iota(parent.begin(), parent.end(), 0);

        // 对于每个区间，回答所有在[l, r]范围内的询问
        // 由于每次回答询问之后，都将其指向了下一个询问
        // 所以若i=find(i)符合i<m && qs[i].first <= r的条件，则必然是一个在 [l,r] 范围内的还没有回答过的询问
        std::vector<int> ans(m, -1);
        for (const std::vector<int> & interval : intervals)
        {
            int l = interval[0], r = interval[1];
            int length = r - l + 1;
            // 二分查找>=区间左端点的最小询问
            int i = std::lower_bound(qs.begin(), qs.end(), std::make_pair(l, -1)) - qs.begin();
            // 回答所有询问位置在[l, r]范围内的还没有被回答过的询问
            for (i = find(i); i < m && qs[i].first <= r; i = find(i + 1))
            {
                ans[qs[i].second] = length;
                parent[i] = i + 1;
            }
        }

        return ans;
    }

private:
    std::vector<int> parent;

    int find(int x)
    {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> intervals = {{2,3},{2,5},{1,8},{20,25}};
    std::vector<int> queries = {2,19,5,22};
    std::vector<int> ans = solution.minInterval(intervals, queries);
    debug::printVector(ans);
    return 0;
}
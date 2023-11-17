#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "debug.h"

class Solution
{
public:
    std::vector<int> maximumSumQueries(std::vector<int> &nums1, std::vector<int> &nums2,
                                       std::vector<std::vector<int>> &queries)
    {
        std::size_t n = nums1.size(), queriesSize = queries.size();
        // 将nums1与nums2组合成二元组(x, y)
        std::vector<std::pair<int, int>> a(n);
        for (int i = 0; i < n; ++i)
        {
            a[i].first = nums1[i];
            a[i].second = nums2[i];
        }
        std::sort(a.begin(), a.end(), std::greater<>());    // 将组合后的二元组(x, y)按照x降序排序

        // 将queries按照x降序排序
        std::vector<int> qid(queriesSize);
        std::iota(qid.begin(), qid.end(), 0);
        std::sort(qid.begin(), qid.end(), [&queries](int i, int j) -> bool { return queries[i][0] > queries[j][0]; });

        std::vector<int> ans(queriesSize);
        std::vector<std::pair<int, int>> stack; // 栈中存放的元素(y, x + y)，栈中y是单调递增的，x + y是单调递减的
        int j = 0;
        for (int i : qid)
        {
            int x = queries[i][0], y = queries[i][1];
            for (; j < n && a[j].first >= x; ++j)
            {
                // 单调栈中的元组的第二个元素(x+y)是严格单调递减的
                while (!stack.empty() && stack.back().second <= a[j].first + a[j].second)
                    stack.pop_back();
                // 单调栈中的元组的第一个元素(y)是严格单调递增的
                if (stack.empty() || stack.back().first < a[j].second)
                    stack.emplace_back(a[j].second, a[j].first + a[j].second);
            }
            // 在单调栈中找到第一个first < y的pair
            auto it = std::lower_bound(stack.begin(), stack.end(), y,
                                       [](const std::pair<int, int> &p, int val) -> bool {
                                           return p.first < val;
                                        });
            ans[i] = (it != stack.end() ? it->second : -1);

            std::cout << "y = " << y << ':';
            for (auto &[first, second] : stack)
            {
                std::cout <<'(' << first << ", " << second << ") ";
            }
            if (ans[i] == -1)
            {
                std::cout << "it == stack.end()" << std::endl;
            }
            else
            {
                std::cout << "it = (" << it->first << ", " << it->second << ") " << std::endl;
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums1 = {4, 3, 1, 2, 6, 2, 7, 1};
    std::vector<int> nums2 = {2, 4, 9, 5, 7, 8, 4, 2};
    std::vector<std::vector<int>> queries = {{4, 1}, {1, 3}, {2, 5}, {6, 1}, {5, 6}, {1, 3}};
    std::vector<int> ans = solution.maximumSumQueries(nums1, nums2, queries);
    debug::printVector(ans);
    return 0;
}

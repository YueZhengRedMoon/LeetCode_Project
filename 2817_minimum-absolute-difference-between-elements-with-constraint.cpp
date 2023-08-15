#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <set>
#include "debug.h"

class SegmentTree
{
public:
    SegmentTree(const std::vector<int> &nums) : size(nums.size()), tree(4 * size)
    {
        build(nums, 1, 0, size - 1);
    }

    std::pair<int, int> query(int qLeft, int qRight)
    {
        return query(1, 0, size - 1, qLeft, qRight);
    }

private:
    int size;
    std::vector<std::pair<int, int>> tree;  // first:min, second:max

    void build(const std::vector<int> &nums, int idx, int left, int right)
    {
        if (left == right)
        {
            tree[idx].first = nums[left];
            tree[idx].second = nums[left];
            return;
        }

        int mid = (left + right) / 2, leftChild = 2 * idx, rightChild = 2 * idx + 1;
        build(nums, leftChild, left, mid);
        build(nums, rightChild, mid + 1, right);

        tree[idx].first = std::min(tree[leftChild].first, tree[rightChild].first);
        tree[idx].second = std::max(tree[leftChild].second, tree[rightChild].second);
    }

    // first:min, second:max
    std::pair<int, int> query(int idx, int left, int right, int qLeft, int qRight)
    {
        // 当前区间与查询区间不相交
        if (left > qRight || right < qLeft)
        {
            return {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
        }

        // 当前区间已经完全被查询区间包含
        if (qLeft <= left && right <= qRight)
        {
            return tree[idx];
        }

        int mid = (left + right) / 2;
        auto leftRes = query(idx * 2, left, mid, qLeft, qRight);
        auto rightRes = query(idx * 2 + 1, mid + 1, right, qLeft, qRight);

        return {std::min(leftRes.first, rightRes.first), std::max(leftRes.second, rightRes.second)};
    }
};

/** 错误 */
class Solution
{
public:
    int minAbsoluteDifference(std::vector<int> &nums, int x)
    {
        SegmentTree segmentTree(nums);
        int n = nums.size(), ans = std::numeric_limits<int>::max();
        std::pair<int, int> res;
        for (int i = 0; i < n; ++i)
        {
            std::cout << "nums[" << i << "] = " << nums[i] << std::endl;
            if (i >= x)
            {
                res = segmentTree.query(0, i - x);
                ans = std::min({std::abs(nums[i] - res.first), std::abs(nums[i] - res.second), ans});
                std::cout << "min(0:" << i - x << ") = " << res.first << ", max(0, " << i - x
                          << ") = " << res.second << ", ans = " << ans << std::endl;
            }
            if (i + x < n)
            {
                res = segmentTree.query(i + x, n - 1);
                ans = std::min({std::abs(nums[i] - res.first), std::abs(nums[i] - res.second), ans});
                std::cout << "min(" << i + x << ":" << n - 1 << ") = " << res.first << ", max(" << i + x << ", " << n - 1
                          << ") = " << res.second << ", ans = " << ans << std::endl;
            }
            std::cout << std::endl;
        }
        return ans;
    }
};

class Solution2
{
public:
    int minAbsoluteDifference(std::vector<int> &nums, int x)
    {
        const int inf = std::numeric_limits<int>::max();
        int ans = inf, n = nums.size();
        std::set<int> set = {-inf / 2, inf};
        for (int i = x; i < n; ++i)
        {
            set.insert(nums[i - x]);
            int y = nums[i];
            auto it = set.lower_bound(y);
            ans = std::min({ans, *it - y, y - *(--it)});
        }
        return ans;
    }
};


int main()
{
    Solution solution;
    std::vector<int> nums({19,138,41,162,52,134});
    int ans = solution.minAbsoluteDifference(nums, 2);
    logObj(ans);
    return 0;
}

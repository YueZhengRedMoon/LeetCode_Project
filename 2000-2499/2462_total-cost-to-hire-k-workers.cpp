#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <functional>

class SegmentTree
{
public:
    SegmentTree(std::vector<int>& nums)
    : n(nums.size())
    , tree(2 << (32 - __builtin_clz(n)))
    , a(nums)
    , idx(n)
    {
        build(0, 0, n);
    }

    // 查询nums[begin, end)中的最小值的索引
    int query(int begin, int end)
    {
        return query(0, 0, n, begin, end);
    }

    // 将a[k]更新为val，同时维护相关的区间信息
    void update(int k, int val)
    {
        a[k] = val;
        k = idx[k]; // 找到a[k]对应的节点编号
        while (k > 0)
        {
            k = (k - 1) / 2;
            int leftChild = 2 * k + 1, rightChild = 2 * k + 2;
            if (a[tree[leftChild]] <= a[tree[rightChild]])
            {
                tree[k] = tree[leftChild];
            }
            else
            {
                tree[k] = tree[rightChild];
            }
        }
    }

private:
    int n;
    std::vector<int> tree;
    std::vector<int>& a;
    std::vector<int> idx;   // idx[i]:a[i]对应的节点编号

    void build(int node, int l, int r)
    {
        if (l >= r)
            return;
        if (l + 1 == r)
        {
            tree[node] = l;
            idx[l] = node; // 记录a[l]在线段树中对应的节点编号
            return;
        }
        int mid = l + (r - l) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        build(leftChild, l, mid);
        build(rightChild, mid, r);
        if (a[tree[leftChild]] <= a[tree[rightChild]])
        {
            tree[node] = tree[leftChild];
        }
        else
        {
            tree[node] = tree[rightChild];
        }
    }

    // 在tree[node]维护的区间[l, r)中查询区间[begin, end)的最小值的索引
    int query(int node, int l, int r, int begin, int end)
    {
        if (r <= begin || l >= end)
            return -1;
        if (begin <= l && r <= end)
        {
            return tree[node];
        }
        else
        {
            int mid = l + (r - l) / 2;
            int leftMinIdx = query(2 * node + 1, l, mid, begin, end);
            int rightMinIdx = query(2 * node + 2, mid, r, begin, end);
            if (leftMinIdx == -1)
                return rightMinIdx;
            else if (rightMinIdx == -1)
                return leftMinIdx;
            else if (a[leftMinIdx] <= a[rightMinIdx])
                return leftMinIdx;
            else
                return rightMinIdx;
        }
    }
};

class Solution
{
public:
    long long totalCost(std::vector<int>& costs, int k, int candidates)
    {
        SegmentTree rmq(costs);
        int n = costs.size();
        int leftEnd = std::min(n, candidates);
        int rightBegin = std::max(0, n - candidates);
        long long ans = 0;
        while (k--)
        {
            int leftIdx = rmq.query(0, leftEnd);
            int rightIdx = rmq.query(rightBegin, n);
            int res;
            if (costs[leftIdx] < costs[rightIdx])
                res = 0;
            else if (costs[leftIdx] > costs[rightIdx])
                res = 1;
            else
            {
                if (leftIdx < rightIdx)
                    res = 0;
                else if (leftIdx < rightIdx)
                    res = 1;
                else
                    res = 2;
            }
            if (res == 0)
            {
                ans += costs[leftIdx];
                rmq.update(leftIdx, INT_MAX);
                leftEnd = std::min(leftEnd + 1, n);
            }
            else if (res == 1)
            {
                ans += costs[rightIdx];
                rmq.update(rightIdx, INT_MAX);
                rightBegin = std::max(rightBegin - 1, 0);
            }
            else    // leftIdx == rightIdx
            {
                ans += costs[leftIdx];
                rmq.update(leftIdx, INT_MAX);
                leftEnd = std::min(leftEnd + 1, n);
                rightBegin = std::max(rightBegin - 1, 0);
            }

            std::cout << "k = " << k << ", ans = " << ans << std::endl;
        }
        return ans;
    }
};

class Solution2
{
public:
    using MinHeap = std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>>;

    long long totalCost(std::vector<int>& costs, int k, int candidates)
    {
        int n = costs.size();
        int leftEnd = std::min(candidates, n), rightBegin = std::max(0, n - candidates);
        auto compare = [&](int i, int j) -> bool {
            if (costs[i] == costs[j])
                return i > j;
            else
                return costs[i] > costs[j];
        };
        MinHeap lpq(compare);
        MinHeap rpq(compare);
        std::vector<bool> used(n, false);

        for (int i = 0; i < leftEnd; ++i)
            lpq.push(i);
        for (int i = rightBegin; i < n; ++i)
            rpq.push(i);

        long long ans = 0;
        while (k--)
        {
            while (used[lpq.top()])
                lpq.pop();
            while (used[rpq.top()])
                rpq.pop();

            int leftIdx = lpq.top(), rightIdx = rpq.top();
            int res = costs[leftIdx] == costs[rightIdx] ? leftIdx - rightIdx : costs[leftIdx] - costs[rightIdx];
            int idx;
            if (res <= 0)
            {
                idx = leftIdx;
                used[leftIdx] = true;
                lpq.pop();
                while (leftEnd < n && used[leftEnd])
                    ++leftEnd;
                if (leftEnd < n)
                    lpq.push(leftEnd++);
            }
            if (res >= 0)
            {
                idx = rightIdx;
                used[rightIdx] = true;
                rpq.pop();
                --rightBegin;
                while (rightBegin >= 0 && used[rightBegin])
                    --rightBegin;
                if (rightBegin >= 0)
                    rpq.push(rightBegin);
            }
            ans += costs[idx];
        }

        return ans;
    }
};

int main()
{
    Solution2 solution2;
    Solution solution1;
    std::vector<int> costs = {980,719,216,384,883,283,880,230,882,142,806,218,604,299,285,949,237,319,680,278,143,697,
                              406,464,962,415,325,99,636,577,701,205,38,154,130,232,897,188,831,467,278,492,159,368,998,
                              572,870,794,949,939,904,15,505,996,767,562,414,65,473,841,400,18,260,410,615,902,266,732,
                              543,746,686,804,714,318,756,803,826,843,297,369,950,495,379,2,919,283,397,463,271,132,
                              40,452,366,269,276,283,563,281,697,878};
    int k = 59;
    int candidates = 15;
    long long ans = solution2.totalCost(costs, k, candidates);
    std::cout << ans << std::endl;
    return 0;
}

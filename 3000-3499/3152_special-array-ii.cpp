#include <iostream>
#include <vector>
#include "../debug/debug.h"

class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& nums)
    : arr(nums), n(nums.size()), tree(2 << (32 - __builtin_clz(n)))
    {
        build(0, 0, n);
    }

    // 查询nums[from, to]是否是特殊数组
    bool query(int from, int to)
    {
        return query(0, 0, n, from, to + 1);
    }

private:
    const std::vector<int>& arr;
    int n;
    std::vector<bool> tree;

    // 预处理构建线段树，tree[node]表示nums[l, r)是否是特殊数组
    void build(int node, int l, int r)
    {
        // 区间长度<=1，是特殊数组
        if (r - l <= 1)
        {
            tree[node] = true;
            return;
        }

        int mid = l + (r - l) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        build(leftChild, l, mid);
        build(rightChild, mid, r);
        tree[node] = tree[leftChild] && tree[rightChild] &&
                    ((mid - l == 0) || (r - mid == 0) || (arr[mid - 1] % 2 != arr[mid] % 2));
    }

    // 在tree[node]所表示的区间[l, r)中查询区间[from, to)是否是特殊数组
    int query(int node, int l, int r, int from, int to)
    {
        if (r <= from || l >= to)
        {
            // 返回-1表示空区间
            return -1;
        }

        if (from <= l && r <= to)
        {
            return tree[node];
        }

        int mid = l + (r - l) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        int leftIsSpecial = query(leftChild, l, mid, from, to);
        if (leftIsSpecial == 0)
            return 0;

        int rightIsSpecial = query(rightChild, mid, r, from, to);
        if (rightIsSpecial == 0)
            return 0;

        bool isSpecial = ((leftIsSpecial == -1) || (rightIsSpecial == -1) || (arr[mid - 1] % 2 != arr[mid] % 2));
        std::cout << "node[" << node << "]=[" << l << ", " << r << "), mid = " << mid << ", from = " << from << ", to = " << to
                  << ", leftIsSpecial = " << leftIsSpecial << ", rightIsSpecial = " << rightIsSpecial
                  << ", canSpecial = " << isSpecial <<  std::endl;
        return isSpecial;
    }
};

class Solution
{
public:
    std::vector<bool> isArraySpecial(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        SegmentTree segmentTree(nums);
        std::vector<bool> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            int from = queries[i][0], to = queries[i][1];
            ans[i] = segmentTree.query(from, to);
        }
        return ans;
    }
};

int main()
{
    std::cout << std::boolalpha;
    Solution solution;
    std::vector<int> nums = {4, 10, 10, 2};
    std::vector<std::vector<int>> queries = {{0, 0}};
    std::vector<bool> ans = solution.isArraySpecial(nums, queries);
    debug::printVector(ans);
    return 0;
}

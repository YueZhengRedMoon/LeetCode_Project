#include <iostream>
#include <vector>

class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& a) : n(a.size()), tree(2 << (32 - __builtin_clz(n))), nums(a)
    {
        build(0, 0, n);
    }

    // 查询区间[begin, end)的最小值索引
    int query(int begin, int end)
    {
        return query(0, 0, n, begin, end);
    }

private:
    int n;
    std::vector<int> tree;
    const std::vector<int>& nums;

    // 预处理构建线段树，tree[node]维护区间[l, r)的最小值的最小索引
    void build(int node, int l, int r)
    {
        if (l >= r) // 空区间
            return;
        if (l + 1 == r) // 区间长度为1
        {
            tree[node] = l;
            return;
        }

        int mid = l + (r - l) / 2, leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        build(leftChild, l, mid);
        build(rightChild, mid, r);
        tree[node] = nums[tree[leftChild]] > nums[tree[rightChild]] ? tree[rightChild] : tree[leftChild];
    }

    // 在tree[node]维护的区间[l, r)中查询区间[begin, end)的最小值索引
    int query(int node, int l, int r, int begin, int end)
    {
        if (r <= begin || l >= end)
            return -1;

        // [begin, end)完全包含[l, r)，返回当前节点的值
        if (begin <= l && r <= end)
            return tree[node];

        int mid = l + (r - l) / 2;
        int leftMin = query(2 * node + 1, l, mid, begin, end);
        int rightMin = query(2 * node + 2, mid, r, begin, end);
        if (leftMin == -1)
            return rightMin;
        else if (rightMin == -1)
            return leftMin;
        else
            return nums[leftMin] > nums[rightMin] ? rightMin : leftMin;
    }
};

class Solution
{
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        std::vector<int> ans;
        ans.reserve(k);

        SegmentTree rmq(nums);
        int begin = 0, end = n - k + 1;
        while (k > 0)
        {
            int minIdx = rmq.query(begin, end);
            ans.push_back(nums[minIdx]);
            --k;
            begin = minIdx + 1;
            end = n - k + 1;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

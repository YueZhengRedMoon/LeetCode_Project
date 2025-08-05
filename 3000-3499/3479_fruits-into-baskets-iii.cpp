#include <iostream>
#include <vector>

// 维护区间最大值的线段树
class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& a)
    : n(a.size())
    , tree(2 << (32 - __builtin_clz(n)), -1)
    {
        build(0, 0, n, a);
    }

    // 在tree[node]维护的区间[l, r)中寻找第一个>=x的值，返回其索引，并将其修改为-1，如果不存在这样的值，则返回-1
    int findFirstAndUpdate(int node, int l, int r, int x)
    {
        if (tree[node] < x) // 区间中没有 >= x 的数
            return -1;

        if (l + 1 == r)
        {
            tree[node] = -1;    // 更新为 -1，表示不能放水果
            return l;
        }

        int mid = (l + r) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        int i = findFirstAndUpdate(leftChild, l, mid, x);   // 先在左子树中寻找
        if (i < 0)  // 左子树中没找到
        {
            i = findFirstAndUpdate(rightChild, mid, r, x);  // 在右子树中寻找
        }
        tree[node] = std::max(tree[leftChild], tree[rightChild]);   // 维护线段树
        return i;
    }

private:
    int n;                  // 数组的长度
    std::vector<int> tree;  // 存储线段树的全局数组，每个元素维护一个区间

    // 预处理构建线段树，tree[node]维护区间[l, r)的最大值
    void build(int node, int l, int r, const std::vector<int>& a)
    {
        if (l >= r) // 空区间
            return;

        if (l + 1 == r) // 区间长度为1
        {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        int leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        // 递归处理子空间
        build(leftChild, l ,mid, a);
        build(rightChild, mid, r, a);
        // 基于子区间的值计算当前区间的最小值
        tree[node] = std::max(tree[rightChild], tree[leftChild]);
    }
};

class Solution
{
public:
    int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets)
    {
        SegmentTree segmentTree(baskets);
        int ans = 0, n = baskets.size();
        for (int x : fruits)
        {
            if (segmentTree.findFirstAndUpdate(0, 0, n, x) < 0)
                ++ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

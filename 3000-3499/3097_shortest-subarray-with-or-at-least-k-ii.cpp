#include <iostream>
#include <vector>

// 维护任意一个区间的元素按位或的值的线段树
class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& a)
    : n(a.size())
    , tree(2 << (32 - __builtin_clz(n)), 0)
    {
        // 预构建线段树
        build(0, 0, n, a);
    }

    // 查询区间[begin, end)的按位或值
    int query(int begin, int end)
    {
        return query(0, 0, n, begin, end);
    }

private:
    int n;                  // 数组的长度
    std::vector<int> tree;  // 存储线段树的全局数组，每个元素维护一个区间

    // 预处理构建线段树，tree[node]维护区间[l, r)的按位或的值
    void build(int node, int l, int r, const std::vector<int>& a)
    {
        if (l >= r) // 空区间
            return;

        if (l + 1 == r) // 区间长度为1
        {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2, leftChild = 2 * node + 1, rightChild = 2 * node + 2;
        // 递归处理子区间
        build(leftChild, l, mid, a);
        build(rightChild, mid, r, a);
        // 基于子区间的按位或值计算当前区间的按位或值
        tree[node] = tree[leftChild] | tree[rightChild];
    }

    // 在tree[node]维护的区间[l, r)中查询区间[begin, end)的按位或值
    int query(int node, int l, int r, int begin, int end)
    {
        // 区间[l, r)和区间[begin, end)不相交，返回0
        if (r <= begin || l >= end)
            return 0;

        // [begin, end)完全包含[l, r)，返回当前节点的值
        if (begin <= l && r <= end)
        {
            return tree[node];
        }
        // 在子节点中进一步查询
        else
        {
            int mid = (l + r) / 2;
            int leftRes = query(2 * node + 1, l, mid, begin, end);
            int rightRes = query(2 * node + 2, mid, r, begin, end);
            return leftRes | rightRes;
        }
    }
};

class Solution
{
public:
    int minimumSubarrayLength(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        SegmentTree segmentTree(nums);

        // 检查nums中是否有长度为len的子数组，它的所有元素按位或运算OR的值至少为k
        auto check = [&](int len) -> bool {
            for (int i = 0, j = len; j <= n; ++i, ++j)
            {
                if (segmentTree.query(i, j) >= k)
                    return true;
            }
            return false;
        };

        int left = 1, right = n + 1, ans = -1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (check(mid))
            {
                ans = mid;
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    int minimumSubarrayLength(std::vector<int>& nums, int k)
    {
        int ans = INT_MAX, left = 0, bottom = 0, rightOr = 0;
        for (int right = 0; right < nums.size(); ++right)
        {
            rightOr |= nums[right];
            while (left <= right && (nums[left] | rightOr) >= k)
            {
                ans = std::min(ans, right - left + 1);  // nums[left, right]按位或的值至少为k
                ++left;
                if (bottom < left)
                {
                    // 重新构建一个栈
                    for (int i = right - 1; i >= left; --i)
                    {
                        nums[i] |= nums[i + 1];
                    }
                    bottom = right;
                    rightOr = 0;
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

class Solution3
{
public:
    int minimumSubarrayLength(std::vector<int>& nums, int k)
    {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            int x = nums[i];
            if (x >= k)
                return 1;

            for (int j = i - 1; j >= 0 && (nums[j] | x) != nums[j]; --j)    // (nums[j] | x) != nums[j]说明x不是nums[j]的子集
            {
                nums[j] |= x;
                if (nums[j] >= k)
                    ans = std::min(ans, i - j + 1);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

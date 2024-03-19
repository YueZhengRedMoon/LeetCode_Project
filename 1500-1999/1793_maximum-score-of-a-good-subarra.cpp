#include <iostream>
#include <vector>
#include <limits>
#include <stack>

namespace TimeLimit
{
    class SegmentTree
    {
    public:
        SegmentTree(const std::vector<int>& numsRef)
                : nums(numsRef)
                , n(nums.size())
                , tree(4 * n)
        {
            build(0, 0, n - 1);
        }

        int query(int left, int right)
        {
            return query(0, 0, n - 1, left, right);
        }

    private:
        const std::vector<int>& nums;
        int n;
        std::vector<int> tree;

        void build(int node, int left, int right)
        {
            if (left > right)
                return;
            if (left == right)
            {
                tree[node] = nums[left];
                return;
            }
            int mid = (left + right) / 2, leftChild = node * 2 + 1, rightChild = node * 2 + 2;
            build(leftChild, left, mid);
            build(rightChild, mid + 1, right);
            tree[node] = std::min(tree[leftChild], tree[rightChild]);
        }

        int query(int node, int left, int right, int queryLeft, int queryRight)
        {
            if (queryRight < left || queryLeft > right)
            {
                return std::numeric_limits<int>::max();
            }
            if (queryLeft == left && queryRight == right)
            {
                return tree[node];
            }
            int mid = (left + right) / 2, leftChild = node * 2 + 1, rightChild = node * 2 + 2;
            if (queryRight <= mid)
            {
                return query(leftChild, left, mid, queryLeft, queryRight);
            }
            else if (queryLeft > mid)
            {
                return query(rightChild, mid + 1, right, queryLeft, queryRight);
            }
            else
            {
                return std::min(query(leftChild, left, mid, queryLeft, mid),
                                query(rightChild, mid + 1, right, mid + 1, queryRight));
            }
        }
    };

    class Solution
    {
    public:
        int maximumScore(std::vector<int>& nums, int k)
        {
            SegmentTree segmentTree(nums);
            int ans = 0, n = nums.size();
            for (int i = k; i >= 0; --i)
            {
                for (int j = k; j < n; ++j)
                {
                    ans = std::max(ans, (j - i + 1) * segmentTree.query(i, j));
                }
            }
            return ans;
        }
    };
}

namespace Solution1
{
    class Solution
    {
    public:
        int maximumScore(std::vector<int>& nums, int k)
        {
            int n = nums.size();

            // 单调递增栈计算每个数左边第一个更小的数的位置
            std::stack<int> leftStack;
            std::vector<int> left(n, -1);   // left[i]:nums[i]左边第一个比nums[i]小的数的下标，如果不存在，则为-1
            for (int i = 0; i < n; ++i)
            {
                while (!leftStack.empty() && nums[leftStack.top()] >= nums[i])
                    leftStack.pop();
                if (!leftStack.empty())
                    left[i] = leftStack.top();
                leftStack.push(i);
            }

            // 单调递增栈计算每个数右边第一个更小的数的位置
            std::stack<int> rightStack;
            std::vector<int> right(n, n);   // right[i]:nums[i]右边第一个比nums[i]小的数的下标
            for (int i = n - 1; i >= 0; --i)
            {
                while (!rightStack.empty() && nums[rightStack.top()] >= nums[i])
                    rightStack.pop();
                if (!rightStack.empty())
                    right[i] = rightStack.top();
                rightStack.push(i);
            }

            int ans = 0;
            for (int i = 0; i < n; ++i)
            {
                if (left[i] < k && k < right[i])
                {
                    ans = std::max(ans, (right[i] - left[i] - 1) * nums[i]);
                }
            }
            return ans;
        }
    };
}

class Solution
{
public:
    int maximumScore(std::vector<int>& nums, int k)
    {
        int n = nums.size(), ans = nums[k], minH = nums[k], i = k, j = k;
        for (int t = 0; t < n - 1; ++t)
        {
            if (j == n - 1 || i && nums[i - 1] > nums[j + 1])
                minH = std::min(minH, nums[--i]);
            else
                minH = std::min(minH, nums[++j]);
            ans = std::max(ans, minH * (j - i + 1));
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

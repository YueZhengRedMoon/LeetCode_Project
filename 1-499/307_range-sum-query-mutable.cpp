#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

namespace Solution1
{
    class NumArray
    {
    public:
        NumArray(std::vector<int> &nums)
        : nums(nums)
        , size(std::sqrt(nums.size()))
        , sum((nums.size() + size - 1) / size, 0)
        {
            for (int i = 0; i < nums.size(); ++i)
            {
                sum[i / size] += nums[i];
            }
        }

        void update(int index, int val)
        {
            sum[index / size] += val - nums[index];
            nums[index] = val;
        }

        int sumRange(int left, int right)
        {
            int b1 = left / size, i1 = left % size, b2 = right / size, i2 = right % size;
            if (b1 == b2)
            {
                // 区间[left, right]在同一块中
                return std::accumulate(nums.begin() + b1 * size + i1, nums.begin() + b1 * size + i2 + 1, 0);
            }
            int sum1 = std::accumulate(nums.begin() + b1 * size + i1, nums.begin() + b1 * size + size, 0);
            int sum2 = std::accumulate(nums.begin() + b2 * size, nums.begin() + b2 * size + i2 + 1, 0);
            int sum3 = std::accumulate(sum.begin() + b1 + 1, sum.begin() + b2, 0);
            return sum1 + sum2 + sum3;
        }

    private:
        std::vector<int> &nums;
        std::size_t size;       // 块的大小
        std::vector<int> sum;   // sum[i]表示第i个块的元素和
    };
}

class SegmentTree
{
public:
    SegmentTree(const std::vector<int> &nums) : n(nums.size()), tree(4 * n)
    {
        build(0, 0, n - 1, nums);
    }

    void update(int index, int value)
    {
        update(index, value, 0, 0, n - 1);
    }

    int rangeSum(int left, int right)
    {
        return rangeSum(left, right, 0, 0, n - 1);
    }

private:
    int n;
    std::vector<int> tree;

    void build(int node, int begin, int end, const std::vector<int> &nums)
    {
        if (begin == end)
        {
            tree[node] = nums[begin];
            return;
        }
        int mid = (begin + end) / 2, leftChild = node * 2 + 1, rightChild = node * 2 + 2;
        build(leftChild, begin, mid, nums);
        build(rightChild, mid + 1, end, nums);
        tree[node] = tree[leftChild] + tree[rightChild];
    }

    void update(int index, int value, int node, int begin, int end)
    {
        if (begin == end)
        {
            tree[node] = value;
            return;
        }
        int mid = (begin + end) / 2, leftChild = node * 2 + 1, rightChild = node * 2 + 2;
        if (index <= mid)
            update(index, value, leftChild, begin, mid);
        else
            update(index, value, rightChild, mid + 1, end);
        tree[node] = tree[leftChild] + tree[rightChild];
    }

    int rangeSum(int left, int right, int node, int begin, int end)
    {
         if (left == begin && right == end)
             return tree[node];
         int mid = (begin + end) / 2, leftChild = node * 2 + 1, rightChild = node * 2 + 2;
         if (right <= mid)
             return rangeSum(left, right, leftChild, begin, mid);
         else if (left > mid)
             return rangeSum(left, right, rightChild, mid + 1, end);
         else
             return rangeSum(left, mid, leftChild, begin, mid) + rangeSum(mid + 1, right, rightChild, mid + 1, end);
    }
};

class NumArray
{
public:
    NumArray(std::vector<int> &nums) : segmentTree(nums) {}

    void update(int index, int val)
    {
        segmentTree.update(index, val);
    }

    int sumRange(int left, int right)
    {
        return segmentTree.rangeSum(left, right);
    }

private:
    SegmentTree segmentTree;
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "../debug/debug.h"

class Solution
{
public:
    int maxSizeSlices(std::vector<int> &slices)
    {
        int n = slices.size();
        int ans1 = calculate(slices, 0, n - 2);
        int ans2 = calculate(slices, 1, n - 1);
        return std::max(ans1, ans2);
    }

private:
    int calculate(const std::vector<int> &slices, int begin, int end)
    {
        constexpr int inf = 0x3f3f3f3f;
        int len = slices.size();
        int n = len / 3;
        // dp[i][j]:从前i个数中选择j个不相邻的数所能取得的最大值
        std::vector<std::vector<int>> dp(len, std::vector<int>(n + 1, -inf));

        dp[begin][0] = 0;
        dp[begin][1] = slices[begin];
        dp[begin + 1][0] = 0;
        dp[begin + 1][1] = std::max(slices[begin], slices[begin + 1]);

        for (int i = begin + 2; i <= end; ++i)
        {
            dp[i][0] = 0;
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i]);
            }
        }

        return dp[end][n];
    }
};

class Solution2
{
public:
    int maxSizeSlices(std::vector<int> &slices)
    {
        int n = slices.size();
        int ans1 = calculate(slices, 0, n - 2);
        int ans2 = calculate(slices, 1, n - 1);
        return std::max(ans1, ans2);
    }

private:
    int calculate(const std::vector<int> &slices, int begin, int end)
    {
        constexpr int inf = 0x3f3f3f3f;
        int N = slices.size();
        int n = N / 3;
        // dp[i][j]:从前i个数中选择j个不相邻的数所能取得的最大值
        std::vector<std::vector<int>> dp(3, std::vector<int>(n + 1, -inf));

        dp[begin][0] = 0;
        dp[begin][1] = slices[begin];
        dp[begin + 1][0] = 0;
        dp[begin + 1][1] = std::max(slices[begin], slices[begin + 1]);

        for (int i = begin + 2; i <= end; ++i)
        {
            int cur = (i % 3), last1 = (i - 1) % 3, last2 = (i - 2) % 3;
            dp[cur][0] = 0;
            for (int j = 1; j <= std::min(i, n); ++j)
            {
                dp[cur][j] = std::max(dp[last1][j], dp[last2][j - 1] + slices[i]);
            }
        }

        return dp[end % 3][n];
    }
};

struct Node
{
    int val;
    int id;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;

    Node(int value, int index, const std::shared_ptr<Node> &prevPtr, const std::shared_ptr<Node> &nextPtr) :
    val(value), id(index), prev(prevPtr), next(nextPtr) {}
};

class MaxHeap
{
public:
    MaxHeap(int heapSize) : heap(heapSize), size(0) {}

    std::shared_ptr<Node> pop()
    {
        // 堆顶的最大值
        std::shared_ptr<Node> top = heap[0];
        // 要提到根的值
        std::shared_ptr<Node> x = heap[--size];
        // 从根开始向下交换
        int i = 0;
        while (i * 2 + 1 < size)
        {
            int left = i * 2 + 1, right = i * 2 + 2;
            int max = left; // 左右孩子中的最大值
            if (right < size && heap[right]->val > heap[left]->val)
                max = right;

            // 已经满足大顶堆的性质
            if (heap[max]->val <= x->val)
                break;

            // 把子节点的值提上来
            std::swap(heap[i], heap[max]);
            i = max;
        }
        heap[i] = x;
        return top;
    }

    void push(const std::shared_ptr<Node> &node)
    {
        int i = size++;
        while (i > 0)
        {
            // 父节点的编号
            int p = (i - 1) / 2;

            // 已经满足大顶堆的性质，退出
            if (heap[p]->val >= node->val)
                break;

            heap[i] = heap[p];
            i = p;
        }
        heap[i] = node;
    }

private:
    std::vector<std::shared_ptr<Node>> heap;
    int size;
};

class Solution3
{
public:
    int maxSizeSlices(std::vector<int> &slices)
    {
        int n = slices.size();
        int k = n / 3;
        MaxHeap maxHeap(n + k);

        // 双向链表
        std::shared_ptr<Node> head = std::make_shared<Node>(slices[0], 0, nullptr, nullptr);
        maxHeap.push(head);
        std::shared_ptr<Node> p = head;
        for (int i = 1; i < n; ++i)
        {
            std::shared_ptr<Node> newNode = std::make_shared<Node>(slices[i], i, p, nullptr);
            p->next = newNode;
            p = newNode;
            maxHeap.push(p);
        }
        p->next = head;
        head->prev = p;

        std::vector<bool> isValid(n, true);
        int ans = 0;
        while (k)
        {
            std::shared_ptr<Node> top = maxHeap.pop();
            if (!isValid[top->id])
                continue;

            ans += top->val;
            std::shared_ptr<Node> left = top->prev, right = top->next;
            top->val = left->val + right->val - top->val;
            maxHeap.push(top);
            isValid[left->id] = false;
            isValid[right->id] = false;

            left->prev->next = top;
            top->prev = left->prev;
            right->next->prev = top;
            top->next = right->next;

            --k;
        }

        return ans;
    }
};

int main()
{
    Solution3 solution;
    std::vector<int> slices = {4, 1, 9, 12, 5, 7, 3, 8, 10};
    int ans = solution.maxSizeSlices(slices);
    logObj(ans);
    return 0;
}

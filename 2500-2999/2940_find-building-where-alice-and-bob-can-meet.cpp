#include <iostream>
#include <vector>
#include <queue>

// 离线+最小堆
class Solution1
{
public:
    using Pair = std::pair<int, int>;

    std::vector<int> leftmostBuildingQueries(std::vector<int>& heights, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> ans(queries.size(), -1);
        std::vector<std::vector<Pair>> qs(heights.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            int a = queries[i][0], b = queries[i][1];
            if (a > b)
            {
                // 保证a < b
                std::swap(a, b);
            }

            if (a == b || heights[a] < heights[b])
            {
                // a直接跳到b
                ans[i] = b;
            }
            else
            {
                // 离线查询
                // 在位置b记录：b的左边有个heights[a]，它属于第i个询问
                qs[b].emplace_back(heights[a], i);
            }
        }

        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> minHeap;
        for (int i = 0; i < heights.size(); ++i)
        {
            while (!minHeap.empty() && minHeap.top().first < heights[i])
            {
                // 小定堆堆顶的heights[a]可以跳到heights[i]
                ans[minHeap.top().second] = i;
                minHeap.pop();
            }
            for (const Pair& p : qs[i])
            {
                // i处的查询后面再回答
                minHeap.emplace(p);
            }
        }

        return ans;
    }
};

// 离线+单调栈二分
class Solution2
{
public:
    using Pair = std::pair<int, int>;

    std::vector<int> leftmostBuildingQueries(std::vector<int>& heights, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> ans(queries.size());
        std::vector<std::vector<Pair>> qs(heights.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            int a = queries[i][0], b = queries[i][1];
            if (a > b)
                std::swap(a, b);

            if (a == b || heights[a] < heights[b])
            {
                ans[i] = b;
                continue;
            }

            qs[b].emplace_back(a, i);
        }

        std::vector<int> decStack;  // vector实现的单调递减栈，vector中从左到右元素是递减的
        for (int b = (int) heights.size() - 1; b >= 0; --b)
        {
            for (const Pair& p : qs[b])
            {
                int a = p.first, i = p.second;

                // 在单调递减栈中找到最后一个大于heights[a]的元素
                int left = 0, right = decStack.size(), res = -1;
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    if (heights[decStack[mid]] > heights[a])
                    {
                        res = decStack[mid];
                        left = mid + 1;
                    }
                    else
                    {
                        right = mid;
                    }
                }
                ans[i] = res;
            }

            while (!decStack.empty() && heights[b] >= heights[decStack.back()])
            {
                decStack.pop_back();
            }
            decStack.push_back(b);
        }

        return ans;
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        std::vector<int> leftmostBuildingQueries(std::vector<int>& heights, std::vector<std::vector<int>>& queries)
        {
            int n = heights.size();

            // nextHigher[i]:i右边第一个高度>heights[i]的建筑物的索引
            std::vector<int> nextHigher(n, -1);
            std::vector<int> decStack;
            decStack.reserve(n);
            for (int i = n - 1; i >= 0; --i)
            {
                while (!decStack.empty() && heights[i] >= heights[decStack.back()])
                {
                    decStack.pop_back();
                }
                if (!decStack.empty())
                {
                    nextHigher[i] = decStack.back();
                }
                decStack.push_back(i);
            }

            std::vector<int> ans(queries.size());
            for (int i = 0; i < queries.size(); ++i)
            {
                int a = queries[i][0], b = queries[i][1];
                if (a == b)
                {
                    ans[i] = a;
                    continue;
                }
                else if (a > b)
                {
                    std::swap(a, b);
                }

                if (heights[a] < heights[b])
                {
                    ans[i] = b;
                    continue;
                }

                int j = b, h = std::max(heights[a], heights[b]);
                while (j != -1 && heights[j] <= h)
                {
                    j = nextHigher[j];
                }
                ans[i] = j;
            }

            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

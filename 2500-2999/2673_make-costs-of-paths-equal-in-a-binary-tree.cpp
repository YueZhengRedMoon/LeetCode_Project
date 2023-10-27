#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int minIncrements(int n, std::vector<int> &cost)
    {
        std::queue<int> queue;
        queue.push(0);
        int maxPathValue = 0;
        int leafStart = -1;
        while (!queue.empty())
        {
            int i = queue.front();
            queue.pop();
            // i不是叶子节点
            if (2 * i + 2 < n)
            {
                cost[2 * i + 1] += cost[i];
                cost[2 * i + 2] += cost[i];
                queue.push(2 * i + 1);
                queue.push(2 * i + 2);
            }
            // i是叶子节点
            else
            {
                if (cost[i] > maxPathValue)
                    maxPathValue = cost[i];
                // 记录叶子节点的开始索引
                if (leafStart == -1)
                    leafStart = i;
            }
        }

        int result = 0;
        for (int i = leafStart; i < n - 1; i += 2)
        {
            result += std::abs(cost[i] - cost[i + 1]);
            queue.push(maxPathValue - std::max(cost[i], cost[i + 1]));
        }

        while (queue.size() >= 2)
        {
            int left = queue.front();
            queue.pop();
            int right = queue.front();
            queue.pop();
            result += std::abs(left - right);
            queue.push(std::min(left, right));
        }

        return result;
    }
};

class Solution2
{
public:
    int minIncrements(int n, std::vector<int> &cost)
    {
        int ans = 0;
        for (int i = n / 2; i > 0; --i)
        {
            ans += std::abs(cost[2 * i - 1] - cost[2 * i]);
            cost[i - 1] += std::max(cost[2 * i - 1], cost[2 * i]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

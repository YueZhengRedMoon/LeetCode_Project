#include <iostream>
#include <unordered_set>
#include <queue>

class Solution
{
public:
    int minimumOneBitOperations(int n)
    {
        if (n == 0)
            return 0;
        int k = 32 - __builtin_clz(n);  // n的二进制长度
        return (1 << k) - 1 - minimumOneBitOperations(n - (1 << (k - 1)));
    }
};

class WrongSolution
{
public:
    int minimumOneBitOperations(int n)
    {
        std::unordered_set<int> isVisited;
        isVisited.insert(n);
        int ans = -1;
        std::queue<std::pair<int, int>> q;
        q.emplace(n, 0);
        while (!q.empty())
        {
            auto [x, step] = q.front();
            q.pop();

            if (x == 0)
            {
                ans = step;
                break;
            }

            ++step;
            // 操作1:翻转x最低位
            int nx = x ^ 1;
            if (isVisited.find(nx) != isVisited.end())
            {
                q.emplace(nx, step);
                isVisited.insert(nx);
            }

            // 操作2:翻转x最低位1左边的位
            nx = x ^ ((x & (-x)) << 1);
            if (isVisited.find(nx) != isVisited.end())
            {
                q.emplace(nx, step);
                isVisited.insert(nx);
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
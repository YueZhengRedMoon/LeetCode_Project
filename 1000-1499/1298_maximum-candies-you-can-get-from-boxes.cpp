#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int maxCandies(std::vector<int>& status, std::vector<int>& candies, std::vector<std::vector<int>>& keys,
                   std::vector<std::vector<int>>& containedBoxes, std::vector<int>& initialBoxes)
    {
        int n = status.size();

        std::vector<int> inDeg(n, 0);
        std::queue<int> q;
        for (int x = 0; x < n; ++x)
        {
            for (int y : containedBoxes[x])
            {
                ++inDeg[y];
            }
            if (status[x] == 0)
            {
                ++inDeg[x];
            }
        }
        for (int x : initialBoxes)
        {
            if (status[x])
            {
                inDeg[x] = 0;
                q.push(x);
            }
        }

        int ans = 0;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            ans += candies[x];
            std::cout << "打开盒子 " << x << ", 获得 " << candies[x] << "个糖果，当前获得糖果数：" << ans << std::endl;

            for (int y : containedBoxes[x])
            {
                if (--inDeg[y] == 0)
                {
                    q.push(y);
                    std::cout << "获得盒子" << y << std::endl;
                }
            }
            for (int y : keys[x])
            {
                if (status[y] == 0) // 盒子处于关闭状态
                {
                    status[y] = 1;  // 用钥匙将盒子打开
                    if (--inDeg[y] == 0)
                    {
                        q.push(y);
                    }
                    std::cout << "获得钥匙" << y << std::endl;
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> status = {1,0,1,0};
    std::vector<int> candies = {7,5,4,100};
    std::vector<std::vector<int>> keys = {{}, {}, {}, {}};
    std::vector<std::vector<int>> containedBoxes = {{1, 2}, {3}, {}, {}};
    std::vector<int> initialBoxes = {1, 2};
    int ans = solution.maxCandies(status, candies, keys, containedBoxes, initialBoxes);
    std::cout << ans << std::endl;
    return 0;
}

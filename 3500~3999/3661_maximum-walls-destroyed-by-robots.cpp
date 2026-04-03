#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Robot
{
    int x;  // 机器人的位置
    int d;  // 机器人的射程
};

class Solution
{
public:
    int maxWalls(std::vector<int>& positions, std::vector<int>& distance, std::vector<int>& walls)
    {
        int n = positions.size();
        std::vector<Robot> robots(n + 2);
        for (int i = 0; i < n; ++i)
        {
            robots[i] = {positions[i], distance[i]};
        }
        robots[n + 1].x = INT_MAX;

        std::sort(robots.begin(), robots.end(), [](const Robot& a, const Robot& b) {return a.x < b.x;});
        std::sort(walls.begin(), walls.end());

        // f[i][0/1]:对于（排序，添加哨兵后的）下标在 [1,i] 中的机器人，在机器人 i+1 往左/右射击的前提下，能摧毁的最大墙壁数量。
        std::vector<std::array<int, 2>> f(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            auto [x, d] = robots[i];

            // 往左射，墙的坐标范围为[leftX, x]
            int leftX = std::max(x - d, robots[i - 1].x + 1);   // +1 表示不能射到左边那个机器人
            int left = std::lower_bound(walls.begin(), walls.end(), leftX) - walls.begin(); // 二分查找到位置>=leftX的最左边的墙的序号
            int cur = std::upper_bound(walls.begin(), walls.end(), x) - walls.begin();  // 二分查找到位置>x的最左边的墙的序号
            int leftRes = f[i - 1][0] + cur - left; // 下标在 [left, cur-1] 中的墙都能摧毁

            cur = std::lower_bound(walls.begin(), walls.end(), x) - walls.begin();  // 二分查找到位置>=x的最左边的墙的序号
            for (int j = 0; j < 2; ++j)
            {
                // 往右射，墙的坐标范围为 [x, rightX]
                auto [x2, d2] = robots[i + 1];
                if (j == 0) // 右边那个机器人往左射
                {
                    x2 -= d2;
                }
                int rightX = std::min(x + d, x2 - 1);   // -1 表示不能射到右边那个机器人（或者它往左射到的墙）
                int right = std::upper_bound(walls.begin(), walls.end(), rightX) - walls.begin();   // 二分查找到位置>=rightX的最左边的墙的序号
                f[i][j] = std::max(leftRes, f[i - 1][1] + right - cur); // 下标在 [cur, right-1] 中的墙都能摧毁
            }
        }
        return f[n][1];
    }
};

class WrongSolution
{
public:
    int maxWalls(std::vector<int>& robots, std::vector<int>& distance, std::vector<int>& walls)
    {
        int n = robots.size(), m = walls.size();
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);

        // 将机器人按照位置排序
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {return robots[a] < robots[b];});
        // 将墙按照位置排序
        std::sort(walls.begin(), walls.end());

        // shooter[i].first:墙排序后，第i堵墙可以被其左边的哪个机器人摧毁，等于-1表示其左边没有机器人可以摧毁它
        // shooter[i].second:墙排序后，第i堵墙可以被其右边的哪个机器人摧毁，等于-1表示其右边没有机器人可以摧毁它
        std::vector<std::pair<int, int>> shooter(m, {-1, -1});
        for (int i : idx)   // 遍历每个机器人
        {
            int pos = robots[i], dis = distance[i];
            int leftRange = pos - dis, rightRange = pos + dis;    // 机器人i的射击覆盖范围[leftRange, rightRange] = [pos-dis, pos+dis]

            // 二分查找机器人i左边可以射到的墙
            int left = 0, right = m, wallIdx = -1;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (walls[mid] <= pos)
                {
                    if (walls[mid] >= leftRange)
                    {
                        wallIdx = mid;
                    }
                    left = mid + 1;
                }
                else    // walls[mid] > pos
                {
                    right = mid;
                }
            }
            if (wallIdx != -1)
            {
                shooter[wallIdx].first = i;
            }

            // 二分查找机器人i右边可以射到的墙
            left = 0;
            right = m;
            wallIdx = -1;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (walls[mid] >= pos)
                {
                    if (walls[mid] <= rightRange)
                    {
                        wallIdx = mid;
                    }
                    right = mid;
                }
                else    // walls[mid] < pos
                {
                    left = mid + 1;
                }
            }
            if (wallIdx != -1)
            {
                shooter[wallIdx].second = i;
            }
        }   // 遍历每个机器人完成

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            if (shooter[i].first != -1)
            {
                ++ans;
                if (shooter[i].first == shooter[i].second && i + 1 < m && shooter[i + 1].first == shooter[i].second)
                {
                    shooter[i + 1].first = -1;
                }
            }
            else if (shooter[i].second != -1)
            {
                ++ans;
                if (i + 1 < m && shooter[i + 1].first == shooter[i].second)
                {
                    shooter[i + 1].first = -1;
                }
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
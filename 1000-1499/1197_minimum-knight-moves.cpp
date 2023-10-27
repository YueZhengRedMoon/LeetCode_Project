#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution
{
public:
    int minKnightMoves(int dx, int dy)
    {
        const int dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2},
                               {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
        std::unordered_map<int, int> minStep;
        std::queue<std::tuple<int, int, int>> queue;
        minStep[hash(0, 0)] = 0;
        queue.emplace(0, 0, 0);

        while (!queue.empty())
        {
            auto [x, y, step] = queue.front();
            queue.pop();
            if (step > minStep[hash(x, y)])
            {
                continue;
            }

            if (x == dx && y == dy)
            {
                return step;
            }

            int nextStep = step + 1;
            for (int i = 0; i < 8; ++i)
            {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                int hashVal = hash(nx, ny);
                auto it = minStep.find(hashVal);
                if (it == minStep.end() || it->second > nextStep)
                {
                    minStep[hashVal] = nextStep;
                    queue.emplace(nx, ny, nextStep);
                }
            }
        }

        return -1;
    }

private:
    inline int hash(int x, int y)
    {
        return (x + 301) * 10000 + y;
    }
};

class Solution2
{
public:
    int minKnightMoves(int x, int y)
    {
        if (x == 0 && y == 0)
            return 0;

        // 4个象限关于（0，0）对称，都转化成第一象限
        x = std::abs(x);
        y = std::abs(y);

        const int dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2},
                               {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

        // 记忆化BFS
        std::queue<std::pair<int, int>> queue;
        std::unordered_set<int> visited;
        queue.emplace(0, 0);
        visited.emplace(hash(0, 0));
        int step = 0;
        while (true)
        {
            int size = queue.size();
            ++step;
            while (size--)
            {
                auto [curX, curY] = queue.front();
                queue.pop();
                for (int i = 0; i < 8; ++i)
                {
                    int nx = curX + dir[i][0], ny = curY + dir[i][1];
                    if (visited.find(hash(nx, ny)) == visited.end())
                    {
                        // 将搜索的范围限定在（0,0）和终点框成的正方形，之外再向外延伸2层的正方形区域中
                        if (-5 <= nx && nx <= x + 5 && -5 <= ny && ny <= y + 5)
                        {
                            if (nx == x && ny == y)
                                return step;
                            queue.emplace(nx, ny);
                            visited.emplace(hash(nx, ny));
                        }
                    }
                }
            }
        }
    }

private:
    inline int hash(int x, int y)
    {
        return (x + 301) * 10000 + y;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
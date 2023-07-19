#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Solution
{
public:
    void wallsAndGates(std::vector<std::vector<int>> &rooms)
    {
        int m = rooms.size(), n = rooms[0].size();
        const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        std::list<std::queue<std::pair<int, int>>> queues;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (rooms[i][j] == 0)
                {
                    std::queue<std::pair<int, int>> queue;
                    queue.emplace(i, j);
                    queues.push_back(std::move(queue));
                }
            }
        }

        while (!queues.empty())
        {
            auto it = queues.begin();
            while (it != queues.end())
            {
                std::queue<std::pair<int, int>> &queue = *it;
                int queueSize = queue.size();
                for (int i = 0; i < queueSize; ++i)
                {
                    auto [x, y] = queue.front();
                    queue.pop();
                    int nextDis = rooms[x][y] + 1;
                    for (int j = 0; j < 4; ++j)
                    {
                        int nx = x + dir[j][0], ny = y + dir[j][1];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && rooms[nx][ny] != -1 && rooms[nx][ny] > nextDis)
                        {
                            rooms[nx][ny] = nextDis;
                            queue.emplace(nx, ny);
                        }
                    }
                }
                if (queue.empty())
                {
                    auto delIt = it;
                    ++it;
                    queues.erase(delIt);
                }
                else
                {
                    ++it;
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
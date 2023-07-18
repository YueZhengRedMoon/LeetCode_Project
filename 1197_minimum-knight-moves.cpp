#include <iostream>
#include <unordered_map>
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

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
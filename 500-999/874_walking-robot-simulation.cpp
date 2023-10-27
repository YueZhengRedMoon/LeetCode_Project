#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    int robotSim(std::vector<int> &commands, std::vector<std::vector<int>> &obstacles)
    {
        std::unordered_map<int, std::unordered_set<int>> obs;
        for (const std::vector<int> &obstacle : obstacles)
        {
            int x = obstacle[0], y = obstacle[1];
            obs[x].emplace(y);
        }

        auto isValid = [&](int x, int y) {
            auto it = obs.find(x);
            return it == obs.end() || it->second.find(y) == it->second.end();
        };

        int curX = 0, curY = 0, dirX = 0, dirY = 1, ans = 0;
        for (int command : commands)
        {
            // 左转90度
            if (command == -2)
            {
                turnLeft(dirX, dirY);
            }
            // 右转90度
            else if (command == -1)
            {
                turnRight(dirX, dirY);
            }
            else
            {
                for (int i = 0; i < command; ++i)
                {
                    int nextX = curX + dirX, nextY = curY + dirY;
                    if (isValid(nextX, nextY))
                    {
                        curX = nextX;
                        curY = nextY;
                        ans = std::max(ans, curX * curX + curY * curY);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        return ans;
    }

private:
    inline void turnLeft(int &dirX, int &dirY)
    {
        // 0,1 -> -1,0
        // 0,-1 -> 1,0
        if (dirX == 0)
        {
            dirX = -dirY;
            dirY = 0;
        }
        // -1,0 -> 0,-1
        // 1,0 -> 0,1
        else
        {
            dirY = dirX;
            dirX = 0;
        }
    }

    inline void turnRight(int &dirX, int &dirY)
    {
        // 0,1 -> 1,0
        // 0,-1 -> -1,0
        if (dirX == 0)
        {
            dirX = dirY;
            dirY = 0;
        }
        // 1,0 -> 0,-1
        // -1,0 -> 0,1
        else
        {
            dirY = -dirX;
            dirX = 0;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <tuple>

class Robot
{
public:
    Robot(int width, int height) : w(width), h(height), s(0) {}

    void step(int num)
    {
        // 由于机器人只能走外圈，那么走 (w+h-2)*2 步后会回到起点
        // 把 s 取模调整到 [1, (w+h-2)*2]，这样不需要特判 s == 0 时的方向
        s = (s + num - 1) % ((w + h - 2) * 2) + 1;
    }

    std::vector<int> getPos()
    {
        auto [x, y, _] = getState();
        return {x, y};
    }

    std::string getDir()
    {
        return std::get<2>(getState());
    }

private:
    int w;
    int h;
    int s;  // 移动的总步数 mod 网格的周长(w + h - 2) * 2

    std::tuple<int, int, std::string> getState()
    {
        if (s < w)
        {
            return {s, 0, "East"};
        }
        else if (s < w + h - 1)
        {
            return {w - 1, s - w + 1, "North"};
        }
        else if (s < w * 2 + h - 2)
        {
            return {w * 2 + h - s - 3, h - 1, "West"};
        }
        else
        {
            return {0, (w + h) * 2 - s - 4, "South"};
        }
    }
};


namespace TimeLimitSolution
{
    class Robot
    {
    public:
        Robot(int width, int height) : w(width), h(height), posI(0), posJ(0), curDir(0), dirStr({"East", "North", "West", "South"})
        {

        }

        void step(int num)
        {
            while (num > 0)
            {
                int deltaI = num * dir[curDir][0], deltaJ = num * dir[curDir][1];
                switch (curDir)
                {
                    case 0: // 往东走
                        if (posJ + deltaJ >= w) // 往东走越界
                        {
                            int delta = w - posJ - 1;
                            posJ = w - 1;   // posI不变，posJ到达网格东边界
                            num -= delta;
                            curDir = 1; // 方向由 East -> North
                        }
                        else    // 往东走没有越界
                        {
                            posJ += deltaJ; // posI不变，posJ往东(+deltaJ)
                            num = 0;
                        }
                        break;
                    case 1: // 往北走
                        if (posI + deltaI >= h) // 往北走越界
                        {
                            int delta = h - posI - 1;
                            posI = h - 1;   // posI到达网格北边界，posJ不变
                            num -= delta;
                            curDir = 2; // 方向由 North -> West
                        }
                        else    // 往北走没有越界
                        {
                            posI += deltaI; // posI往北(+deltaI)，posJ不变
                            num = 0;
                        }
                        break;
                    case 2: // 往西走
                        if (posJ + deltaJ < 0)  // 往西走越界
                        {
                            int delta = posJ;
                            posJ = 0;   // posI不变，posJ到达网格西边界
                            num -= delta;
                            curDir = 3; // 方向由 West -> South
                        }
                        else    // 往西走没有越界
                        {
                            posJ += deltaJ; // posI不变，posJ往西(+deltaJ)
                            num = 0;
                        }
                        break;
                    case 3: // 往南走
                        if (posI + deltaI < 0)  // 往南走越界
                        {
                            int delta = posI;
                            posI = 0;   // posI到达网格南边界, posJ不变
                            num -= delta;
                            curDir = 0; // 方向由 South -> East
                        }
                        else    // 往南走没有越界
                        {
                            posI += deltaI; // posI往南(+deltaI)，posJ不变
                            num = 0;
                        }
                        break;
                }
            }
        }

        std::vector<int> getPos()
        {
            return {posI, posJ};
        }

        std::string getDir()
        {
            return dirStr[curDir];
        }

    private:
        int w;
        int h;
        int posI;
        int posJ;
        // East:(0,1) North:(1,0) West:(0,-1) South:(-1,0)
        int curDir;
        constexpr static int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        std::vector<std::string> dirStr;
    };
}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>

class Solution
{
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t)
    {
        // 从起点到终点最小要走多少步
        int minStep = std::max(std::abs(sx - fx), std::abs(sy - fy));
        if (minStep > t)
            return false;
        if (minStep == 0 && t > 0)
            return false;
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
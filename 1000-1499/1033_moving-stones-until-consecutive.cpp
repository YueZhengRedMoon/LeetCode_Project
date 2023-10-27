#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> numMovesStones(int a, int b, int c)
    {
        std::vector<int> stones({a, b, c});
        std::sort(stones.begin(), stones.end());

        int a2b = stones[1] - stones[0];
        int b2c = stones[2] - stones[1];

        // 最小的移动次数
        int minimumMoves;
        if (a2b == 1)
            minimumMoves = (b2c == 1 ? 0 : 1);
        else if (b2c == 1)
            minimumMoves = 1;
        else if (a2b == 2 || b2c == 2)
            minimumMoves = 1;
        else
            minimumMoves = 2;

        // 最大的移动次数
        int maximumMoves = a2b + b2c - 2;

        return {minimumMoves, maximumMoves};
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
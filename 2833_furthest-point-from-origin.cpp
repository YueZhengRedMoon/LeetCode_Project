#include <iostream>
#include <vector>

class Solution
{
public:
    int furthestDistanceFromOrigin(std::string moves)
    {
        int n = moves.size();
        int lCnt = 0, rCnt = 0;
        for (char c : moves)
        {
            if (c == 'L')
                ++lCnt;
            else if (c == 'R')
                ++rCnt;
        }
        return std::abs(lCnt - rCnt) + n - lCnt - rCnt;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

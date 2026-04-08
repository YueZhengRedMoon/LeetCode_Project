#include <iostream>
#include <vector>

class Solution
{
public:
    int minCost(std::vector<int>& startPos, std::vector<int>& homePos, std::vector<int>& rowCosts, std::vector<int>& colCosts)
    {
        int ans = 0;
        if (startPos[0] != homePos[0])
        {
            int delta = startPos[0] < homePos[0] ? 1 : -1;
            int r = startPos[0];
            do
            {
                r += delta;
                ans += rowCosts[r];
            } while (r != homePos[0]);
        }
        if (startPos[1] != homePos[1])
        {
            int delta = startPos[1] < homePos[1] ? 1 : -1;
            int c = startPos[1];
            do
            {
                c += delta;
                ans += colCosts[c];
            } while (c != homePos[1]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
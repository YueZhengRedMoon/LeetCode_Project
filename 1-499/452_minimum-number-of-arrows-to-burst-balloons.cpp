#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findMinArrowShots(std::vector<std::vector<int>> &points)
    {
        std::sort(points.begin(), points.end(), less);
        int shots = 1;
        int rightmost = points[0][1];
        for (int i = 1; i < points.size(); ++i)
        {
            if (points[i][0] > rightmost)
            {
                ++shots;
                rightmost = points[i][1];
            }
            else
            {
                rightmost = std::min(rightmost, points[i][1]);
            }
        }
        return shots;
    }

private:
    static bool less(const std::vector<int> &lhs, const std::vector<int> &rhs)
    {
        if (lhs[0] == rhs[0])
        {
            return lhs[1] < rhs[1];
        }
        else
        {
            return lhs[0] < rhs[0];
        }
    }
};

int main() {
    return 0;
}
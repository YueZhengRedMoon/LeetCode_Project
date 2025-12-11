#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int countCoveredBuildings(int n, std::vector<std::vector<int>>& buildings)
    {
        // rangeXofY[y]:纵坐标为y的建筑中，最小的x(first)和最大的x(second)
        // rangeYofX[x]:横坐标为x的建筑中，最小的y(first)和最大的y(second)
        std::unordered_map<int, std::pair<int, int>> rangeXofY, rangeYofX;
        for (int i = 0; i < buildings.size(); ++i)
        {
            int x = buildings[i][0], y = buildings[i][1];

            auto it = rangeXofY.find(y);
            if (it == rangeXofY.end())
            {
                rangeXofY.emplace(y, std::make_pair(x, x));
            }
            else
            {
                std::pair<int, int>& rangeX = it->second;
                if (x < rangeX.first)
                    rangeX.first = x;
                else if (x > rangeX.second)
                    rangeX.second = x;
            }

            it = rangeYofX.find(x);
            if (it == rangeYofX.end())
            {
                rangeYofX.emplace(x, std::make_pair(y, y));
            }
            else
            {
                std::pair<int, int>& rangeY = it->second;
                if (y < rangeY.first)
                    rangeY.first = y;
                else if (y > rangeY.second)
                    rangeY.second = y;
            }
        }

        int ans = 0;
        for (int i = 0; i < buildings.size(); ++i)
        {
            int x = buildings[i][0], y = buildings[i][1];

            const std::pair<int, int> &rangeX = rangeXofY[y], &rangeY = rangeYofX[x];
            if (rangeX.first < x && x < rangeX.second && rangeY.first < y && y < rangeY.second)
                ++ans;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> buildings = {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}};

    return 0;
}
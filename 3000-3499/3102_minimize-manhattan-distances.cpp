#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Solution
{
public:
    int minimumDistance(std::vector<std::vector<int>>& points)
    {
        std::multiset<int> xs, ys;
        for (const auto& p : points)
        {
            // 将一个点(x, y)的坐标变为(x+y, x-y)后，原坐标系中的曼哈顿距离等于新坐标系中的切比雪夫距离
            // (x1, y1)与(x2, y2)的切比雪夫距离定义为max(|x1-x2|, |y1-y2|)
            xs.insert(p[0] + p[1]);
            ys.insert(p[0] - p[1]);
        }
        int ans = INT_MAX;
        for (const auto& p : points)
        {
            int x = p[0] + p[1], y = p[0] - p[1];
            xs.erase(xs.find(x));
            ys.erase(ys.find(y));
            ans = std::min(ans, std::max(*xs.rbegin() - *xs.begin(), *ys.rbegin() - *ys.begin()));
            xs.insert(x);
            ys.insert(y);
        }
        return ans;
    }
};

class Solution2
{
public:
    int minimumDistance(std::vector<std::vector<int>>& points)
    {
        int maxX1 = INT_MIN, maxX2 = INT_MIN, maxY1 = INT_MIN, maxY2 = INT_MIN; // x, y坐标转换后的最大值与次大值
        int minX1 = INT_MAX, minX2 = INT_MAX, minY1 = INT_MAX, minY2 = INT_MAX; // x, y坐标转换后的最小值与次小值
        for (const auto& p : points)
        {
            int x = p[0] + p[1], y = p[0] - p[1];
            // 更新转换后x坐标的最大值与次大值
            if (x >= maxX1)
            {
                maxX2 = maxX1;
                maxX1 = x;
            }
            else if (x > maxX2)
            {
                maxX2 = x;
            }
            // 更新转换后x坐标的最小值与次小值
            if (x <= minX1)
            {
                minX2 = minX1;
                minX1 = x;
            }
            else if (x < minX2)
            {
                minX2 = x;
            }
            // 更新转换后y坐标的最大值与次大值
            if (y >= maxY1)
            {
                maxY2 = maxY1;
                maxY1 = y;
            }
            else if (y > maxY2)
            {
                maxY2 = y;
            }
            // 更新转换后y坐标的最小值与次小值
            if (y <= minY1)
            {
                minY2 = minY1;
                minY1 = y;
            }
            else if (y < minY2)
            {
                minY2 = y;
            }
        }
        int ans = INT_MAX;
        for (const auto& p : points)
        {
            int x = p[0] + p[1], y = p[0] - p[1];
            int dx = (x == maxX1 ? maxX2 : maxX1) - (x == minX1 ? minX2 : minX1);
            int dy = (y == maxY1 ? maxY2 : maxY1) - (y == minY1 ? minY2 : minY1);
            ans = std::min(ans, std::max(dx, dy));
        }
        return ans;
    }
};

class Solution3
{
public:
    int minimumDistance(std::vector<std::vector<int>>& points)
    {
        int maxXi, minXi, maxYi, minYi; // 最大，最小坐标的索引
        int maxX1 = INT_MIN, maxX2 = INT_MIN, maxY1 = INT_MIN, maxY2 = INT_MIN; // x, y坐标转换后的最大值与次大值
        int minX1 = INT_MAX, minX2 = INT_MAX, minY1 = INT_MAX, minY2 = INT_MAX; // x, y坐标转换后的最小值与次小值
        for (int i = 0; i < points.size(); ++i)
        {
            int x = points[i][0] + points[i][1], y = points[i][0] - points[i][1];
            updateMax(i, x, maxXi, maxX1, maxX2);
            updateMax(i, y, maxYi, maxY1, maxY2);
            updateMin(i, x, minXi, minX1, minX2);
            updateMin(i, y, minYi, minY1, minY2);
        }
        int ans = INT_MAX;
        for (int i : {maxXi, minXi, maxYi, minYi})
        {
            int dx = (i == maxXi ? maxX2 : maxX1) - (i == minXi ? minX2 : minX1);
            int dy = (i == maxYi ? maxY2 : maxY1) - (i == minYi ? minY2 : minY1);
            ans = std::min(ans, std::max(dx, dy));
        }
        return ans;
    }

private:
    // 更新最大次大
    void updateMax(int i, int v, int& maxI, int& max1, int& max2)
    {
        if (v > max1)
        {
            maxI = i;
            max2 = max1;
            max1 = v;
        }
        else if (v > max2)
        {
            max2 = v;
        }
    }

    // 更新最小次小
    void updateMin(int i, int v, int& minI, int& min1, int& min2)
    {
        if (v < min1)
        {
            minI = i;
            min2 = min1;
            min1 = v;
        }
        else if (v < min2)
        {
            min2 = v;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

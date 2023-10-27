#include <iostream>
#include <cmath>

class Solution
{
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
    {
        // 圆心在矩形内
        if (x1 <= xCenter && xCenter <= x2 && y1 <= yCenter && yCenter <= y2)
            return true;

        // 半径的平方
        int r2 = radius * radius;

        // 矩形在圆内
        int d2;
        d2 = square(xCenter - x1) + square(yCenter - y1);
        if (d2 <= r2) return true;
        d2 = square(xCenter - x1) + square(yCenter - y2);
        if (d2 <= r2) return true;
        d2 = square(xCenter - x2) + square(yCenter - y1);
        if (d2 <= r2) return true;
        d2 = square(xCenter - x2) + square(yCenter - y2);
        if (d2 <= r2) return true;

        // 正方形的四条边 x = x1, x = x2, y = y1, y = y2
        // 圆的方程(x - xCenter)^2 + (y - yCenter)^2 = radius^2
        // 判断圆是否与矩形的边相交
        int d;
        // 判断圆是否与x = x1相交
        d = std::abs(xCenter - x1);    // 圆心到x = x1的距离
        if (d <= radius)
        {
            double dy = std::sqrt(r2 - square(x1 - xCenter));
            // 交点的y坐标
            double iy1 = yCenter + dy, iy2 = yCenter - dy;
            if ((iy1 >= y1 && iy1 <= y2) || (iy2 >= y1 && iy2 <= y2))
                return true;
        }

        // 判断圆是否与x = x2相交
        d = std::abs(xCenter - x2);
        if (d <= radius)
        {
            double dy = std::sqrt(r2 - square(x2 - xCenter));
            // 交点的y坐标
            double iy1 = yCenter + dy, iy2 = yCenter - dy;
            if ((iy1 >= y1 && iy1 <= y2) || (iy2 >= y1 && iy2 <= y2))
                return true;
        }

        // 判断圆是否与y = y1相交
        d = std::abs(yCenter - y1);
        if (d <= radius)
        {
            double dx = std::sqrt(r2 - square(y1 - yCenter));
            // 交点的x坐标
            double ix1 = xCenter + dx, ix2 = xCenter - dx;
            if ((x1 <= ix1 && ix1 <= x2) || (x1 <= ix2 && ix2 <= x2))
                return true;
        }

        // 判断圆是否与y = y2相交
        d = std::abs(yCenter - y2);
        if (d <= radius)
        {
            double dx = std::sqrt(r2 - square(y2 - yCenter));
            // 交点的x坐标
            double ix1 = xCenter + dx, ix2 = xCenter - dx;
            if ((x1 <= ix1 && ix1 <= x2) || (x1 <= ix2 && ix2 <= x2))
                return true;
        }

        return false;
    }

private:
    inline int square(int x)
    {
        return x * x;
    }
};

class Solution2
{
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
    {
        int dist = 0;
        if (xCenter < x1 || xCenter > x2)
        {
            dist += std::min(square(x1 - xCenter), square(x2 - xCenter));
        }
        if (yCenter < y1 || yCenter > y2)
        {
            dist += std::min(square(y1 - yCenter), square(y2 - yCenter));
        }
        return dist <= radius * radius;
    }

private:
    inline int square(int x)
    {
        return x * x;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
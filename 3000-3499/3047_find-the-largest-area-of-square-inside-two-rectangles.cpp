#include <iostream>
#include <vector>

struct Rectangle
{
    int blX;
    int blY;
    int trX;
    int trY;

    Rectangle(int blx_, int bly_, int trx_, int try_) : blX(blx_), blY(bly_), trX(trx_), trY(try_) {}
};

class Solution
{
public:
    long long largestSquareArea(std::vector<std::vector<int>>& bottomLeft, std::vector<std::vector<int>>& topRight)
    {
        int maxSide = 0;
        int n = bottomLeft.size();
        for (int i = 0; i < n - 1; ++i)
        {
            Rectangle rect1(bottomLeft[i][0], bottomLeft[i][1], topRight[i][0], topRight[i][1]);

            // 如果rect1的长或宽<=maxSide，那么交集矩形的长或宽也<=maxSide，内层循环不会使maxSide变大
            if (std::max(rect1.trX - rect1.blX, rect1.trY - rect1.blY) <= maxSide)
            {
                continue;
            }

            for (int j = i + 1; j < n; ++j)
            {
                Rectangle rect2(bottomLeft[j][0], bottomLeft[j][1], topRight[j][0], topRight[j][1]);
                int side = f(rect1, rect2);
                if (side > maxSide)
                    maxSide = side;
            }
        }
        return (long long) maxSide * maxSide;
    }

private:
    // 计算两个矩形交集区域内的最大正方形的边长
    long long f(const Rectangle& rect1, const Rectangle& rect2)
    {
        // 计算两个矩形在x轴的交集长度
        int lenX = intersectionLen(rect1.blX, rect1.trX, rect2.blX, rect2.trX);

        // 计算两个矩形在y轴的交集长度
        int lenY = intersectionLen(rect1.blY, rect1.trY, rect2.blY, rect2.trY);

        return std::min(lenX, lenY);
    }

    // 求区间(a1, b1)与区间(a2, b2)的交集长度
    int intersectionLen(int a1, int b1, int a2, int b2)
    {
        // 假设(a1, b1)在(a2, b2)的左边
        if (a1 > a2)
        {
            std::swap(a1, a2);
            std::swap(b1, b2);
        }

        // a1 b1 a2 b2：两个区间没有交集
        if (b1 <= a2)
        {
            return 0;
        }
        // a1 a2 b1 b2：两个区间有交集
        else if (b1 <= b2)
        {
            return b1 - a2;
        }
        // a1 a2 b2 b1：区间(a1, b1)包含了区间(a2, b2)
        else
        {
            return b2 - a2;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
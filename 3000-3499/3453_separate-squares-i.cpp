#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Solution
{
public:
    double separateSquares(std::vector<std::vector<int>>& squares)
    {
        int minY = INT_MAX, maxY = INT_MIN;
        for (const std::vector<int>& s : squares)
        {
            int y = s[1], l = s[2];
            minY = std::min(minY, y);
            maxY = std::max(maxY, y + l);
        }

        constexpr double EPS = 1e-5;
        double left = minY, right = maxY;
        while (right - left > EPS)
        {
            double mid = (left + right) / 2.0;

            // 计算上/下区域的面积
            double upArea = 0, downArea = 0;
            for (const std::vector<int>& s : squares)
            {
                int y = s[1], l = s[2];
                if (y < mid)
                {
                    if (y + l <= mid)   // 该正方形完全属于下半区
                    {
                        downArea += l * l;
                    }
                    else    // y + l > mid，该正方形一部分属于下半区，一部分属于上半区
                    {
                        downArea += (mid - y) * l;
                        upArea += (y + l - mid) * l;
                    }
                }
                else    // y >= mid，该正方形属于上半区
                {
                    upArea += l * l;
                }
            }

            double delta = upArea - downArea;
            if (delta > EPS)    // 上半区的面积更大
            {
                left = mid;    // 提升y线
            }
            else if (delta < -EPS)  // 下半区的面积更大
            {
                right = mid;    // 降低y线
            }
            else    // 两个半区的面积一样大
            {
                right = mid;    // 降低y线
            }
        }
        return left;
    }
};

class Solution2
{
public:
    double separateSquares(std::vector<std::vector<int>>& squares)
    {
        long long totalArea = 0;
        std::map<int, long long> diff;
        for (const std::vector<int>& s : squares)
        {
            int y = s[1];
            long long l = s[2];
            totalArea += l * l;
            diff[y] += l;
            diff[y + l] -= l;
        }

        long long area = 0, sumL = 0;
        auto it = diff.begin();
        while (true)
        {
            auto [y, sl] = *it;
            int y2 = (++it)->first;
            sumL += sl; // 矩形底边长度之和
            area += sumL * (y2 - y);
            if (area * 2 >= totalArea)
            {
                return y2 - (area * 2.0 - totalArea) / (sumL * 2.0);
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
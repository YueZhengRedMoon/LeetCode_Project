#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <map>

class Solution
{
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        std::unordered_map<double, std::vector<double>> groups; // 斜率 -> [截距]
        // 平行四边形两条对角线的中点是重合的，按照对角线的中点分组统计，以去除重复的计数
        std::unordered_map<int, std::vector<double>> groups2; // 中点 -> [斜率]

        int n = points.size();
        for (int i = 0; i < n - 1; ++i)
        {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j)
            {
                int x2 = points[j][0], y2 = points[j][1];
                int dx = x1 - x2, dy = y1 - y2;
                double k = dx ? (double) dy / dx : std::numeric_limits<double>::infinity();
                double b = dx ? (double) (y1 * dx - x1 * dy) / dx : x1;
                groups[k].push_back(b);
                int mid = ((x1 + x2 + 2000) << 16) | (y1 + y2 + 2000);  // 把二维坐标压缩成一个 int
                groups2[mid].push_back(k);
            }
        }

        int ans = 0;
        for (auto it = groups.begin(); it != groups.end(); ++it)
        {
            const std::vector<double>& g = it->second;
            if (g.size() == 1)
                continue;

            std::map<double, int> cnt;
            for (double b : g)
            {
                ++cnt[b];
            }
            int s = 0;
            for (const auto& [_, c] : cnt)
            {
                ans += s * c;
                s += c;
            }
        }

        for (auto it = groups2.begin(); it != groups2.end(); ++it)
        {
            const std::vector<double>& g = it->second;
            if (g.size() == 1)
                continue;

            std::map<double, int> cnt;
            for (double k : g)
            {
                ++cnt[k];
            }
            int s = 0;
            for (const auto& [_, c] : cnt)
            {
                ans -= s * c;   // 平行四边形会统计两次，减去多统计的一次
                s += c;
            }
        }

        return ans;
    }
};

// 超时
class TimeLimitSolution
{
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        int n = points.size();

        // 统计任意两点之间的线段的斜率(用分数表示，first表示分子，second表示分母，若second=0，则表示线段垂直于x轴)
        //  - 将线段按照斜率分组
        std::unordered_map<int, std::vector<std::pair<int, int>>> groupK;
        for (int i = 0; i < n - 1; ++i)
        {
            int x1 = points[i][0], y1 = points[i][1];

            for (int j = i + 1; j < n; ++j)
            {
                int x2 = points[j][0], y2 = points[j][1], dx = 0, dy = 0;
                if (x1 != x2)
                {
                    dx = x1 - x2;
                    dy = y1 - y2;
                    int gcd = std::gcd(dx, dy);
                    dx /= gcd;
                    dy /= gcd;

                    // 统一分数的符号位置，如果斜率为负，则将负号放在分子处
                    if (dx * dy < 0)
                    {
                        dy = -std::abs(dy);
                    }
                    // 斜率>= 0，确保去掉负号
                    else
                    {
                        dy = std::abs(dy);
                    }
                    dx = std::abs(dx);
                }
                // else k[i][j] = {0, 0}

                // 将线段按照斜率分组
                groupK[(dy << 16) | dx].emplace_back(i, j);
            }
        }

        // 平行四边形会被被统计两次，用集合去除重复的平行四边形
        std::unordered_set<long long> set;
        for (auto it = groupK.begin(); it != groupK.end(); ++it)
        {
            const std::vector<std::pair<int, int>>& lines = it->second; // 相同斜率的线段
            int m = lines.size();
            for (int i = 0; i < m - 1; ++i)
            {
                int p1 = lines[i].first, p2 = lines[i].second;

                int x1 = points[p1][0], y1 = points[p1][1];
                int x2 = points[p2][0], y2 = points[p2][1];
                for (int j = i + 1; j < m; ++j)
                {
                    int p3 = lines[j].first, p4 = lines[j].second;
                    int x3 = points[p3][0], y3 = points[p3][1];

                    // 若(x1,y1),(x2,y2),(x3,y3),(x4,y4)不在同一条直线上，则它们可以组成一个梯形
                    if (!isIn3PointLine(x1, y1, x2, y2, x3, y3))
                    {
                        std::vector<long long> ps = {p1, p2, p3, p4};
                        std::sort(ps.begin(), ps.end());
                        // 最多有500个点，最多用9位二进制位就能表示一个点
                        set.insert((ps[0] << 27) | (ps[1] << 18) | (ps[2] << 9) | ps[3]);
                    }
                }
            }
        }
        return set.size();
    }

private:
    // 判断(x1,y1),(x2,y2),(x3,y3)是否处于同一条直线上
    bool isIn3PointLine(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        // 三点一线且垂直于x轴
        if (x1 == x2 && x2 == x3)
        {
            return true;
        }

        int dx = x1 - x2, dy = y1 - y2;
        // y = (dy/dx)*x + b => b = y1 - (dy/dx)*x1
        // y3 = (dy/dx)*x3 + y1 - (dy/dx)*x1
        return y3 * dx  == dy * x3 + y1 * dx - dy * x1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
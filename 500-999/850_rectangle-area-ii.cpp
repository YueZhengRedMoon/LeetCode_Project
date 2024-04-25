#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int rectangleArea(std::vector<std::vector<int>>& rectangles)
    {
        const int MOD = 1'000'000'007;
        std::vector<int> xs;   // 所有矩形的左右两条边的横坐标集合
        xs.reserve(rectangles.size() * 2);
        for (const auto& rectangle : rectangles)
        {
            int x1 = rectangle[0], x2 = rectangle[2];
            xs.push_back(x1);
            xs.push_back(x2);
        }
        std::sort(xs.begin(), xs.end()); // 将所有边的横坐标排序
        long long ans = 0;
        for (int i = 1; i < xs.size(); ++i) // 扫描线
        {
            int left = xs[i - 1], right = xs[i];
            if (left == right)
                continue;

            std::vector<std::pair<int, int>> lines;
            for (const auto& rectangle : rectangles)
            {
                int x1 = rectangle[0], y1 = rectangle[1], x2 = rectangle[2], y2 = rectangle[3];
                if (x1 <= left && right <= x2)
                    lines.emplace_back(y1, y2);
            }
            std::sort(lines.begin(), lines.end());

            long long high = 0, down = -1, up = -1;
            for (auto [y1, y2] : lines)
            {
                if (y1 > up)
                {
                    high += up - down;
                    down = y1;
                    up = y2;
                }
                else if (y2 > up)   // y1 <= up
                {
                    up = y2;
                }
            }
            high += up - down;
            ans = (ans + (right - left) * high) % MOD;
        }
        return (int) ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> rectangles = {{0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1}};
    int ans = solution.rectangleArea(rectangles);
    std::cout << ans << std::endl;
    return 0;
}

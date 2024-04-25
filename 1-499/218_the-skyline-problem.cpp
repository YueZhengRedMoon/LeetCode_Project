#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Solution
{
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings)
    {
        std::vector<std::pair<int, int>> ps;    // 存储所有矩形上边左右端点的数组
        ps.reserve(buildings.size() * 2);
        for (const auto& building : buildings)
        {
            int left = building[0], right = building[1], height = building[2];
            ps.emplace_back(left, -height);  // 左端点，高度表示为负数，以便遇到横坐标相同的点时优先处理左端点
            ps.emplace_back(right, height);  // 右端点，高度表示为正数
        }

        // 对所有端点从小到大排序
        // 优先按横坐标排序
        // 横坐标相同。优先处理左端点，后处理右端点
        // 横坐标相同，也都是左/右端点。对于左端点，优先处理高度高的；对于右端点，优先处理高度低的
        std::sort(ps.begin(), ps.end());

        std::vector<std::vector<int>> ans;
        int prev = 0;   // 上一条加入到天际线的“上边”的的高度
        std::multiset<int, std::greater<>> pq;  // 通过红黑树实现的优先队列（大顶堆）
        pq.insert(0);   // 优先队列中至少会存在一个元素0，当一个坐标处没有建筑物时，天际线高度为0
        for (auto [x, y] : ps)   // x:当前上边端点的横坐标, abs(y):当前上边端点的高度
        {
            if (y < 0) // 当前端点是左端点
            {
                pq.insert(-y); // 将左端点高度加入到优先队列中
            }
            else    // 当前端点是右端点
            {
                // 一条上边处理完，移除优先队列中的高度
                auto it = pq.find(y);
                pq.erase(it);
            }

            int cur = *pq.begin();  // 当前优先队列中最高的高度
            if (cur != prev)
            {
                ans.push_back({x, cur});
                prev = cur;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

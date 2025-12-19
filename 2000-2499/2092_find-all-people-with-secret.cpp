#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson)
    {
        // 按照会议时间升序排序
        std::sort(meetings.begin(), meetings.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[2] < b[2];
        });

        // 一开始 0 和 firstPerson 都知道秘密
        std::unordered_set<int> haveSecret = {0, firstPerson};

        // 分组循环
        int m = meetings.size(), i = 0;
        while (i < m)
        {
            // 在同一时间发生的会议，建图
            std::unordered_map<int, std::vector<int>> g;
            int time = meetings[i][2];
            while (i < m && meetings[i][2] == time)
            {
                int x = meetings[i][0], y = meetings[i][1];
                g[x].push_back(y);
                g[y].push_back(x);
                ++i;
            }

            // 每个连通块只要有一个人知道秘密，那么整个连通块的人都知道秘密
            std::unordered_set<int> vis;    // 避免重复访问节点
            std::function<void(int)> dfs = [&](int x) {
                vis.insert(x);
                haveSecret.insert(x);
                for (int y : g[x])
                {
                    if (vis.find(y) == vis.end())
                    {
                        dfs(y);
                    }
                }
            };
            for (auto it = g.begin(); it != g.end(); ++it)  // 遍历在 time 时间点参加会议的专家
            {
                int x = it->first;
                // 从知道秘密的专家出发，DFS 标记其余专家
                if (haveSecret.find(x) != haveSecret.end() && vis.find(x) == vis.end())
                {
                    dfs(x);
                }
            }
        }

        return std::vector<int>(haveSecret.begin(), haveSecret.end());
    }
};

class WrongSolution
{
public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson)
    {
        // 按照会议时间升序排序
        std::sort(meetings.begin(), meetings.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                    return a[2] < b[2];
        });
        const int MAX_T = 100001;
        meetings.push_back({0, firstPerson, MAX_T});    // 为便于处理，在最后加上会议

        std::vector<bool> isKnow(n, false); // isKnow[i]:专家i是否知晓秘密
        isKnow[0] = isKnow[firstPerson] = true;

        std::unordered_map<int, int> peopleMap; // 在同一时刻参加会议的专家编号及其对应的序号
        for (int i = 0, j = 0; j < meetings.size(); ++j)
        {
            if (meetings[j][2] == meetings[i][2])   // meetings[i, j]的会议发生在同一时刻
            {
                int x = meetings[j][0], y = meetings[j][1];
                if (peopleMap.find(x) == peopleMap.end())
                {
                    peopleMap.emplace(x, peopleMap.size());
                }
                if (peopleMap.find(y) == peopleMap.end())
                {
                    peopleMap.emplace(y, peopleMap.size());
                }
            }
            else    // meetings[i, j)的会议发生在同一时刻
            {
                int m = peopleMap.size();       // m个专家在同一时刻参加了meetings[i, j)
                std::vector<int> id2p(m);    // meetings[i, j)中m个专家出现的次序及其对应的专家编号
                for (auto it = peopleMap.begin(); it != peopleMap.end(); ++it)
                {
                    int p = it->first, id = it->second;
                    id2p[id] = p;
                }

                // 初始化并查集
                std::vector<int> parent(m);
                std::iota(parent.begin(), parent.end(), 0);

                // 维护并查集
                for (int k = i; k < j; ++k)
                {
                    int x = meetings[k][0], y = meetings[k][1];
                    unite(id2p, parent, peopleMap[x], peopleMap[y]);
                }

                for (int k = 0; k < m; ++k)
                {
                    int x = id2p[k], y = id2p[find(parent, k)];
                    if (isKnow[y])
                    {
                        isKnow[x] = true;
                        std::cout << "时刻 " << meetings[i][2] << ", 专家 " << x << "知晓秘密" << std::endl;
                    }
                }

                // 重置窗口
                i = j;
                peopleMap.clear();
                peopleMap.emplace(meetings[j][0], 0);
                peopleMap.emplace(meetings[j][1], 1);
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            if (isKnow[i])
                ans.push_back(i);
        }
        return ans;
    }

private:
    int find(std::vector<int>& parent, int x)
    {
        if (x == parent[x])
            return x;
        else
            return parent[x] = find(parent, parent[x]);
    }

    void unite(const std::vector<int>& id2p, std::vector<int>& parent, int x, int y)
    {
        x = find(parent, x);
        y = find(parent, y);

        if (x != y)
        {
            // 编号更小的专家作为父节点
            if (id2p[x] < id2p[y])
            {
                parent[y] = x;
            }
            else
            {
                parent[x] = y;
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
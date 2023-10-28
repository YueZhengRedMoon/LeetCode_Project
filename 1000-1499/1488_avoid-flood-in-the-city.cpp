#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> avoidFlood(std::vector<int> &rains)
    {
        int n = rains.size();
        std::vector<int> ans(n, 1);
        std::set<int> set;
        std::unordered_map<int, int> map;   // key:湖泊，value:下雨的日期
        for (int i = 0; i < n; ++i)
        {
            // 不下雨
            if (rains[i] == 0)
            {
                // 用有序集合记录不下雨的日期
                set.insert(i);
            }
            // 下雨
            else
            {
                ans[i] = -1;
                if (map.find(rains[i]) != map.end())    // 当前湖泊是满的
                {
                    auto it = set.lower_bound(map[rains[i]]);   // 找到第一个在当前湖泊下雨后的晴天
                    if (it == set.end())
                    {
                        // 不存在这样的晴天，无法避免洪水
                        return {};
                    }
                    // 那个晴天排除这个湖泊的水
                    ans[*it] = rains[i];
                    // 这个晴天不再可用
                    set.erase(it);
                }
                map[rains[i]] = i;  // 记录下雨的日期
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> rains = {2,3,0,0,3,1,0,1,0,2,2};
    std::vector<int> ans = solution.avoidFlood(rains);
    if (ans.empty())
        std::cout << "[]" << std::endl;
    else
        debug::printVector(ans);
    return 0;
}

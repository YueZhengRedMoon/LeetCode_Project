#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> countPairs(int n, std::vector<std::vector<int>> &edges, std::vector<int> &queries)
    {
        std::vector<int> deg(n, 0);
        std::unordered_map<int, int> count;
        for (const std::vector<int> &edge : edges)
        {
            int u = edge[0] - 1, v = edge[1] - 1;
            if (u > v)
                std::swap(u, v);
            ++deg[u];
            ++deg[v];
            ++count[(u << 16) | v];
        }
        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(), [&](const int &lhs, const int &rhs) {return deg[lhs] < deg[rhs];});

        int queriesNum = queries.size();
        std::vector<int> ans(queriesNum, 0);
        for (int i = 0; i < queriesNum; ++i)
        {
            int left = 0, right = n - 1;
            while (left < right)
            {
                if (deg[id[left]] + deg[id[right]] <= queries[i])
                {
                    ++left;
                }
                else
                {
                    ans[i] += right - left;
                    --right;
                }
            }

            for (auto [key, cnt] : count)
            {
                int sum = deg[key >> 16] + deg[key & 0xFFFF];
                if (sum > queries[i] && sum - cnt <= queries[i])
                {
                    --ans[i];
                }
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> countPairs(int n, std::vector<std::vector<int>> &edges, std::vector<int> &queries)
    {
        std::vector<int> deg(n, 0);
        std::unordered_map<int, int> edgeCnt;
        for (const auto &edge : edges)
        {
            int u = edge[0] - 1, v = edge[1] - 1;
            if (u > v)
                std::swap(u, v);
            ++deg[u];
            ++deg[v];
            ++edgeCnt[u << 16 | v];
        }

        // 统计deg中元素的出现次数
        std::unordered_map<int, int> degCnt;
        int maxDeg = 0;
        for (int d : deg)
        {
            ++degCnt[d];
            if (d > maxDeg)
                maxDeg = d;
        }

        int k = maxDeg * 2 + 2;
        std::vector<int> cnts(k);
        for (auto [deg1, c1] : degCnt)
        {
            for (auto [deg2, c2] : degCnt)
            {
                if (deg1 < deg2)
                {
                    cnts[deg1 + deg2] += c1 * c2;
                }
                else if (deg1 == deg2)
                {
                    cnts[deg1 + deg2] += c1 * (c1 - 1) / 2;
                }
            }
        }

        for (auto [key, c] : edgeCnt)
        {
            int s = deg[key >> 16] + deg[key & 0xFFFF];
            --cnts[s];
            ++cnts[s - c];
        }

        for (int i = k - 1; i > 0; --i)
        {
            cnts[i - 1] += cnts[i];
        }

        for (int &q : queries)
        {
            q = cnts[std::min(q + 1, k - 1)];
        }

        return queries;
    }
};

int main()
{
    Solution2 solution;
    int n = 4;
    std::vector<std::vector<int>> edges = {{1,2},{2,4},{1,3},{2,3},{2,1}};
    std::vector<int> queries = {2, 3};
    std::vector<int> ans = solution.countPairs(n, edges, queries);
    debug::printVector(ans);
    return 0;
}

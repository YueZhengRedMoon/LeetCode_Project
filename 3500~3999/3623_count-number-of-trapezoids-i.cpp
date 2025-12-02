#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

class Solution
{
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        constexpr int MOD = 1'000'000'007;
        std::unordered_map<int, int> cnt;
        for (const std::vector<int>& p : points)
        {
            ++cnt[p[1]];    // 统计每一行（水平线）有多少个点
        }

        long long ans = 0, s = 0;
        for (auto& [_, c] : cnt)
        {
            long long k = c * (c - 1ll) / 2ll;
            ans += s * k;
            s += k;
        }
        return ans % MOD;
    }
};

class Solution2
{
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        // 按照y坐标升序排序，若y坐标相同，则按x坐标升序排序
        std::sort(points.begin(), points.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
        });

        constexpr int MOD = 1'000'000'007;
        long long ans = 0;
        int curY = INT_MIN;     // 当前正在枚举的Y坐标
        int curCnt = 0;         // 枚举到p时，有多少个点与当前点p的y坐标相同
        long long bottomEdgeCnt = 0;  // 枚举到p时，有多少种水平梯形的底边
        for (const std::vector<int>& p : points)
        {
            int y = p[1];
            if (y == curY)
            {
                ++curCnt;
            }
            else    // y != curY
            {
                long long topEdgeCnt = curCnt * (curCnt - 1ll) / 2ll; // 对纵坐标为curY的点，有多少种水平梯形的顶边
                ans = (ans + bottomEdgeCnt * topEdgeCnt) % MOD;
                bottomEdgeCnt += topEdgeCnt;
                curY = y;
                curCnt = 1;
            }
        }
        long long topEdgeCnt = curCnt * (curCnt - 1ll) / 2ll;
        ans = (ans + bottomEdgeCnt * topEdgeCnt) % MOD;

        return (int) ans;
    }
};

// 超时
class TimeLimitSolution
{
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        // groupYCnt[y]:纵坐标为y的点的数量
        std::unordered_map<int, int> groupYCnt;
        for (const std::vector<int>& p : points)
        {
            ++groupYCnt[p[0]];
        }

        long long ans = 0;
        constexpr int MOD = 1'000'000'007;
        for (auto it1 = groupYCnt.begin(); it1 != groupYCnt.end(); ++it1)
        {
            long long upCnt = comp2(it1->second);

            auto it2 = it1;
            ++it2;
            while (it2 != groupYCnt.end())
            {
                long long bottomCnt = comp2(it2->second);
                ++it2;

                ans = (ans + upCnt * bottomCnt) % MOD;
            }
        }
        return (int) ans;
    }

private:
    // 从n个不同的数中取出2个数的方案数
    int comp2(int n)
    {
        return n * (n - 1) / 2;
    }
};



int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
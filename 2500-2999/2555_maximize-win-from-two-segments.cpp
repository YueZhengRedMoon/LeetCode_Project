#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Solution
{
public:
    int maximizeWin(std::vector<int>& prizePositions, int k)
    {
        int ans = 0, n = prizePositions.size();
        std::queue<std::pair<int, int>> q;  // first:线段中的奖品数, second:线段的右端点
        int maxCnt = -1;
        for (int i = 0; i < n; ++i)
        {
            long long x = prizePositions[i];
            if (i && x == prizePositions[i - 1])
                continue;

            // 找两个重叠的线段，线段重叠后的长度为2 * k - 1
            auto it = std::upper_bound(prizePositions.begin() + i, prizePositions.end(), std::max(x + 2 * k - 1, x));
            int cnt = it - (prizePositions.begin() + i);    // 记录这段长为2 * k - 1的线段中的奖品数
            if (cnt > ans)
                ans = cnt;

            // 找两个不重叠的线段
            it = std::upper_bound(prizePositions.begin() + i, prizePositions.end(), std::max(x + k, x)); // 先找1个长度为k的线段
            cnt = it - (prizePositions.begin() + i);    // 记录这段长为k的线段中的奖品数

            while (!q.empty() && q.front().second < x)
            {
                maxCnt = std::max(maxCnt, q.front().first);
                q.pop();
            }

            ans = std::max(ans, maxCnt + cnt);
            q.emplace(cnt, x + k);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

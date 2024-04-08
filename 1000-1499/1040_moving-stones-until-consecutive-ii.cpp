#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> numMovesStonesII(std::vector<int>& s)
    {
        std::sort(s.begin(), s.end());
        int n = s.size();
        int e1 = s[n - 2] - s[0] - n + 2;   // (s[0], s[n-2])之间的空位数
        int e2 = s[n - 1] - s[1] - n + 2;   // (s[1], s[n-1])之间的空位数
        int maxMove = std::max(e1, e2);
        if (e1 == 0 || e2 == 0) // 特殊情况，没有空位
            return {std::min(2, maxMove), maxMove};
        int maxCnt = 0, left = 0;
        for (int right = 0; right < n; ++right) // 滑动窗口，枚举右端点所在石子
        {
            while (s[right] - s[left] + 1 > n)  // 窗口长度大于n
                ++left; // 缩小窗口长度
            maxCnt = std::max(maxCnt, right - left + 1);    // 维护窗口内最大的石子数
        }
        return {n - maxCnt, maxMove};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

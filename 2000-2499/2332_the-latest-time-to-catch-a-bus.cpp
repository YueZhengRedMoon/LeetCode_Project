#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int latestTimeCatchTheBus(std::vector<int>& buses, std::vector<int>& passengers, int capacity)
    {
        std::sort(buses.begin(), buses.end());
        std::sort(passengers.begin(), passengers.end());

        int i = 0, j = 0, n = buses.size(), m = passengers.size(), ans = 0;
        int waitBegin = 0, waitEnd = 0; // passengers[waitBegin, waitEnd)的乘客在等公交
        while (i < n)   // 遍历每辆公交车发车的时间点
        {
            if (j == m || buses[i] < passengers[j])  // 没有乘客或者下一个时间点公交车先到
            {
                // 已经到达的乘客都上车
                int newWaitBegin = std::min(waitBegin + capacity, waitEnd);
                int cnt = newWaitBegin - waitBegin; // 上车人数
                waitBegin = newWaitBegin;
                if (cnt < capacity && (j == 0 || passengers[j - 1] != buses[i]))
                {
                    // 公交车还有空位，且自己不能和乘客同时到达车站，此时到车站可以上车
                    ans = buses[i];
                }
                ++i;    // 公交发车，等待下一辆公交发车
            }
            else // 还有乘客，且下一个时间点乘客先到
            {
                int waitCnt = waitEnd - waitBegin;              // 当前正在等车的人数
                int busCnt = (waitCnt + capacity) / capacity;   // 装下当前所有已经在等待的乘客和自己需要多少辆公交车
                if (i + busCnt <= n) // 剩下的公交车足够容纳所有正在等待的乘客和自己
                {
                    if (j == 0 || passengers[j - 1] != passengers[j] - 1)    // 自己不能和乘客同时到达
                    {
                        ans = passengers[j] - 1;
                    }
                }
                else    // 剩下的公交车已经没有办法容纳所有正在等待的乘客和自己
                {
                    break;
                }
                // 到达一个乘客
                ++j;
                ++waitEnd;
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

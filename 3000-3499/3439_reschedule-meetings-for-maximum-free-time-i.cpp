#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int maxFreeTime(int eventTime, int k, std::vector<int>& startTime, std::vector<int>& endTime)
    {
        int n = startTime.size();

//        std::vector<int> idx(n);
//        std::iota(idx.begin(), idx.end(), 0);
//        std::sort(idx.begin(), idx.end(), [&](int i, int j) {
//            return startTime[i] < startTime[j];
//        });

        std::vector<int> freeTime;
        freeTime.reserve(n + 1);
        freeTime.push_back(startTime[0]);
        for (int i = 1; i < n; ++i)
        {
            freeTime.push_back(startTime[i] - endTime[i - 1]);
        }
        freeTime.push_back(eventTime - endTime[n - 1]);

        int t = 0, j = 0;
        for (; j < std::min<int>(k + 1, freeTime.size()); ++j)
            t += freeTime[j];
        int ans = t;
        for (int i = 0; j < freeTime.size(); ++i, ++j)
        {
            t += freeTime[j] - freeTime[i];
            if (t > ans)
            {
                ans = t;
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    int eventTime = 99;
    int k = 1;
    std::vector<int> startTime = {7, 21, 25}, endTime = {13, 25, 78};
    int ans = solution.maxFreeTime(eventTime, k, startTime, endTime);
    std::cout << ans << std::endl;
    return 0;
}

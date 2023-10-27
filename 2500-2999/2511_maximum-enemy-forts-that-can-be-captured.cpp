#include <iostream>
#include <vector>
#include <functional>
#include "../debug.h"

class Solution
{
public:
    int captureForts(std::vector<int> &forts)
    {
        int n = forts.size(), ans = 0;
        for (int i = 0, lastN1 = -1, last1 = -1; i < n; ++i)
        {
            if (forts[i] == 1)
            {
                if (lastN1 != -1)
                {
                    ans = std::max(ans, i - lastN1 - 1);
                    lastN1 = -1;
                }
                last1 = i;
            }
            else if (forts[i] == -1)
            {
                if (last1 != -1)
                {
                    ans = std::max(ans, i - last1 - 1);
                    last1 = -1;
                }
                lastN1 = i;
            }
        }
        return ans;
    }
};

// 理解错题意了，只有一支军队能动
class Solution2
{
public:
    int captureForts(std::vector<int> &forts)
    {
        int n = forts.size(), ans = 0;
        std::vector<std::pair<int, int>> intervals;
        for (int i = 0, lastN1 = -1, last1 = -1; i < n; ++i)
        {
            if (forts[i] == 1)
            {
                if (lastN1 != -1)
                {
                    intervals.emplace_back(lastN1, i);
                    lastN1 = -1;
                }
                last1 = i;
            }
            else if (forts[i] == -1)
            {
                if (last1 != -1)
                {
                    intervals.emplace_back(last1, i);
                    last1 = -1;
                }
                lastN1 = i;
            }
        }
        int intervalsNum = intervals.size();

        std::function<void(int, int)> backtracking = [&](int i, int sum) {
            if (i >= intervalsNum)
            {
                if (sum > ans)
                    ans = sum;
                return;
            }

            int capture = intervals[i].second - intervals[i].first - 1;
            if (i == intervalsNum - 1)
            {
                sum += capture;
                if (sum > ans)
                    ans = sum;
                return;
            }

            if (intervals[i + 1].first > intervals[i].second)
            {
                backtracking(i + 1, sum + capture);
            }
            else
            {
                backtracking(i + 1, sum);
                backtracking(i + 2, sum + capture);
            }
        };

        backtracking(0, 0);

        for (auto [b, e] : intervals)
        {
            std::cout << b << ", " << e << std::endl;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> forts = {1,0,0,-1,0,0,-1,0,0,1};
    int ans = solution.captureForts(forts);
    logObj(ans);
    return 0;
}

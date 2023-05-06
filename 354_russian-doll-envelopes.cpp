#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

/** 错误 */
class Solution
{
public:
    int maxEnvelopes(std::vector<std::vector<int>> &envelopes)
    {
        std::sort(envelopes.begin(), envelopes.end(),
                  [](const std::vector<int> &lhs, const std::vector<int> &rhs) -> bool
                  {
                        if (lhs[0] == rhs[0])
                            return lhs[1] < rhs[1];
                        return lhs[0] < rhs[0];
                  });
        // dp[i]:i+1个信封组成一组“俄罗斯套娃”信封，最大的信封的长和宽
        std::vector<std::vector<int>> dp({{0, 0}});
        for (const auto& envelope : envelopes)
        {
            int left = 0, right = dp.size();
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (dp[mid][0] > envelope[0] && dp[mid][1] > envelope[1])
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }

            if (left == dp.size())
            {
                if (envelope[0] > dp.back()[0] && envelope[1] > dp.back()[1])
                {
                    dp.push_back({envelope[0], envelope[1]});
                }
            }
            else
            {
                dp[left][0] = envelope[0];
                dp[left][1] = envelope[1];
            }
        }
        debug::printVector2D(dp);
        return dp.size() - 1;
    }
};

/** 超时 */
class Solution2
{
public:
    int maxEnvelopes(std::vector<std::vector<int>> &envelopes)
    {
        std::sort(envelopes.begin(), envelopes.end(),
                  [](const std::vector<int> &lhs, const std::vector<int> &rhs) -> bool
                  {
                      if (lhs[0] == rhs[0])
                          return lhs[1] < rhs[1];
                      return lhs[0] < rhs[0];
                  });
        std::vector<int> dp(envelopes.size(), 1);
        int result = 1;
        for (int i = 1; i < envelopes.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
                {
                    dp[i] = std::max(dp[j] + 1, dp[i]);
                }
            }
            if (dp[i] > result)
                result = dp[i];
        }

        debug::printVector(dp);
        return result;
    }
};

class Solution3
{
public:
    int maxEnvelopes(std::vector<std::vector<int>> &envelopes)
    {
        // 因为对于信封i,j必须有wj < wi and hi < hj才能将信封j放入到信封j中，
        // 所以当w都相同的时候，显然应该选择最大的h才能尽可能放入最多的信封
        // 按照w升序排序，按照h降序排序
        std::sort(envelopes.begin(), envelopes.end(),
                  [](const std::vector<int> &lhs, const std::vector<int> &rhs)->bool
                  {
                        if (lhs[0] == rhs[0])
                            return lhs[1] > rhs[1];
                        return lhs[0] < rhs[0];
                  });

        debug::printVector2D(envelopes);

        // dp[i]:i个信封组成一组“俄罗斯套娃”信封，最大的信封h
        std::vector<int> dp({envelopes[0][1]});
        for (int i = 1; i < envelopes.size(); ++i)
        {
            if (envelopes[i][1] > dp.back())
            {
                dp.push_back(envelopes[i][1]);
            }
            else
            {
                int index = std::lower_bound(dp.begin(), dp.end(), envelopes[i][1]) - dp.begin();
                dp[index] = envelopes[i][1];
            }
        }
        debug::printVector(dp);
        return dp.size();
    }
};

int main()
{
    Solution3 solution;
    std::vector<std::vector<int>> envelopes({{2,100},{3,200},{4,300},{5,500},{5,400},{5,250},{6,370},{6,360},{7,380}});
    int result = solution.maxEnvelopes(envelopes);
    std::cout << result << std::endl;
    return 0;
}

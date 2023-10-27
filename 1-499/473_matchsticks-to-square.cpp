#include <iostream>
#include <vector>
#include <algorithm>

/** 超时 */
class Solution
{
public:
    bool makesquare(std::vector<int> &matchsticks)
    {
        // 周长
        int perimeter = 0;
        int maxMatchstick = 0;
        for (int matchstick : matchsticks)
        {
            perimeter += matchstick;
            if (matchstick > maxMatchstick)
            {
                maxMatchstick = matchstick;
            }
        }

        if (perimeter % 4 != 0)
        {
            return false;
        }

        // 边长
        int length = perimeter / 4;
        if (maxMatchstick > length)
        {
            return false;
        }


        std::sort(matchsticks.begin(), matchsticks.end());
        std::vector<int> sides(4, length);
        return backtracking(matchsticks, sides, 0);
    }

private:
    bool backtracking(std::vector<int> &matchsticks, std::vector<int> &sides, int start)
    {
        if (sides[0] == 0 && sides[1] == 0 && sides[2] == 0 && sides[3] == 0)
        {
            return true;
        }

        for (int i = 0; i < 4; ++i)
        {
            for (int j = start; j < matchsticks.size() && sides[i] >= matchsticks[j]; ++j)
            {
                sides[i] -= matchsticks[j];
                if (backtracking(matchsticks, sides, j + 1))
                {
                    return true;
                }
                sides[i] += matchsticks[j];
            }
        }

        return false;
    }
};

class Solution2
{
public:
    bool makesquare(std::vector<int> &matchsticks)
    {
        // 周长
        int perimeter = 0;
        int maxMatchstick = 0;
        for (int matchstick : matchsticks)
        {
            perimeter += matchstick;
            if (matchstick > maxMatchstick)
            {
                maxMatchstick = matchstick;
            }
        }

        if (perimeter % 4 != 0)
        {
            return false;
        }

        // 边长
        int length = perimeter / 4;
        if (maxMatchstick > length)
        {
            return false;
        }


        std::sort(matchsticks.begin(), matchsticks.end(), std::greater<int>());
        std::vector<int> sides(4, length);
        return backtracking(matchsticks, sides, 0);
    }

private:
    bool backtracking(std::vector<int> &matchsticks, std::vector<int> &sides, int index)
    {
        if (index == matchsticks.size())
        {
            return true;
        }

        for (int i = 0; i < sides.size(); ++i)
        {
            sides[i] -= matchsticks[index];
            if (sides[i] >= 0 && backtracking(matchsticks, sides, index + 1))
            {
                return true;
            }
            sides[i] += matchsticks[index];
        }
        return false;
    }
};

class Solution3
{
public:
    bool makesquare(std::vector<int> &matchsticks)
    {
        // 周长
        int perimeter = 0;
        int maxMatchstick = 0;
        for (int matchstick : matchsticks)
        {
            perimeter += matchstick;
            if (matchstick > maxMatchstick)
            {
                maxMatchstick = matchstick;
            }
        }

        if (perimeter % 4 != 0)
        {
            return false;
        }

        // 边长
        int length = perimeter / 4;
        if (maxMatchstick > length)
        {
            return false;
        }

        int n = matchsticks.size();
        // dp[s]:表示正方形未放满的边的当前长度
        std::vector<int> dp(1 << n, -1);
        dp[0] = 0;

        // 状态s记录哪些火柴已经被放入(s的第k位为1表示第k根火柴已经被放入)
        for (int s = 1; s < (1 << n); ++s)
        {
            for (int k = 0; k < n; ++k)
            {
                // 状态s没有放入第k根火柴
                if ((s & (1 << k)) == 0)
                {
                    continue;
                }

                // s1状态与s状态的区别仅在于s状态拿了第k根火柴，而s1状态没有拿第k根火柴
                int s1 = s & ~(1 << k);
                if (dp[s1] >= 0 && dp[s1] + matchsticks[k] <= length)
                {
                    dp[s] = (dp[s1] + matchsticks[k]) % length;
                    break;
                }
            }
        }
        return dp[(1 << n) - 1] == 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int countSpecialNumbers(int n)
    {
        std::string s = std::to_string(n);
        int m = s.length();
        std::vector<std::vector<int>> memo(m, std::vector<int>(1024, -1));  // -1表示没有计算过

        // 从i(0 <= i < m)开始填比特集mask中未出现的数字
        // isLimit表示前面填的数字是否都正好是n对应位上的数字
        //      -isLimit = True:i最多只能填到int(s[i])
        //      -isLimit = False:i可以填到9
        // isNum表示前面填的数字是否可以构成数，如果前面填的数都是0（即前导0），则尚不构成数，isNum = False，否则isNum = True
        //      -isNum = True:前面填的数字已经构成数，可以从0开始填
        //      -isNum = False:前面没有填数（全是前导0），可以继续不填，或从1开始填
        std::function<int(int, int, bool, bool)> f = [&](int i, int mask, bool isLimit, bool isNum) -> int
        {
            if (i == m)
                return isNum;   // isNum位 true 表示得到了一个合法数字
            if (!isLimit && isNum && memo[i][mask] != -1)
                return memo[i][mask];

            int res = 0;
            if (!isNum)
                res = f(i + 1, mask, false, false); // 继续跳过当前数

            int up = isLimit ? s[i] - '0' : 9;  // 当前可以填的数的上界
            for (int d = 1 - isNum; d <= up; ++d)   // 枚举要填入当前位置的数
            {
                if (((1 << d) & mask) == 0) // d不在mask中
                    res += f(i + 1, mask | (1 << d), isLimit && d == up, true);
            }

            if (!isLimit && isNum)
                memo[i][mask] = res;

            return res;
        };

        return f(0, 0, true, false);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>

/** 错误 */
class Solution
{
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        int currentMin = 1;
        int currentSum = 0;
        while (currentMin <= maxChoosableInteger)
        {
            if (currentSum + maxChoosableInteger >= desiredTotal)
            {
                return true;
            }
            else
            {
                currentSum += currentMin;
                ++currentMin;
            }

            if (currentMin <= maxChoosableInteger)
            {
                if (currentSum + maxChoosableInteger >= desiredTotal)
                {
                    return false;
                }
                else
                {
                    currentSum += currentMin;
                    ++currentMin;
                }
            }
        }
        return false;
    }
};

class Solution2
{
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        // 所有可选的数累加起来都无法达到desiredTotal，先手必不能赢
        if ((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal)
        {
            return false;
        }

        return dfs(maxChoosableInteger, 0, desiredTotal, 0);
    }

private:
    std::unordered_map<int, bool> memo;

    bool dfs(int maxChoosableInteger, int usedNumbers, int desiredTotal, int currentTotal)
    {
        if (memo.find(usedNumbers) == memo.end())
        {
            bool result = false;
            // 遍历每一个可选的数
            for (int i = 0; i < maxChoosableInteger; ++i)
            {
                // i没有选过
                if (((1 << i) & usedNumbers) == 0)
                {
                    // i要加1,因为i从0开始
                    // 选上这个数后达到目标和，赢了
                    if (i + 1 + currentTotal >= desiredTotal)
                    {
                        result = true;
                        break;
                    }

                    // 如果下一个dfs的结果是假，也就是说下次是另一个人走，他必输，那我必赢
                    if (!dfs(maxChoosableInteger, usedNumbers | (1 << i), desiredTotal, currentTotal + i + 1))
                    {
                        result = true;
                        break;
                    }
                }
            }
            memo[usedNumbers] = result;
        }
        return memo[usedNumbers];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

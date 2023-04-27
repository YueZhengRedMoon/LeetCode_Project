#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int minimumOperations(std::string leaves)
    {
        int leavesSize = leaves.size();
        // left[i]:将leaves[0:i]全部替换成红叶需要的调整次数
        std::vector<int> left(leavesSize, 0);
        left[0] = (leaves[0] == 'r' ? 0 : 1);
        for (int i = 1; i < leavesSize; ++i)
        {
            if (leaves[i] == 'r')
                left[i] = left[i - 1];
            else
                left[i] = left[i - 1] + 1;
        }

        // right[i]:将leaves[i:leavesSize)全部替换成红叶需要的调整次数
        std::vector<int> right(leavesSize, 0);
        right[leavesSize - 1] = (leaves[leavesSize - 1] == 'r' ? 0 : 1);
        for (int i = leavesSize - 2; i >= 0; --i)
        {
            if (leaves[i] == 'r')
                right[i] = right[i + 1];
            else
                right[i] = right[i + 1] + 1;
        }

        // dp[i]:将leaves[0:i]替换成[红、黄]两部分需要的最少调整次数
        std::vector<int> dp(leavesSize);
        dp[0] = left[0];
        int result = leavesSize;
        for (int i = 1; i < leavesSize - 1; ++i)
        {
            // 红叶
            if (leaves[i] == 'r')
            {
                dp[i] = std::min(dp[i - 1] + 1, left[i - 1] + 1);
            }
            // 黄叶
            else
            {
                dp[i] = std::min(dp[i - 1], left[i - 1]);
            }
            result = std::min(result, dp[i] + right[i + 1]);
        }

        return result;
    }
};

class Solution2
{
public:
    int minimumOperations(std::string leaves)
    {
        int n = leaves.size();
        // dp[i][j]:对leaves[0:i]进行调整操作，并且第i片叶子处于状态j时的最小操作次数
        // j = 0:第i片叶子是前面的红色部分
        // j = 1:第i片叶子是中间的黄色部分
        // j = 2:第i片叶子是后面的红色部分
        std::vector<std::vector<int>> dp(n, std::vector<int>(3));
        dp[0][0] = (leaves[0] == 'y');
        dp[0][1] = dp[0][2] = dp[1][2] = std::numeric_limits<int>::max();   // 无意义的状态，取值为无穷大

        for (int i = 1; i < n; ++i)
        {
            int isRed = (leaves[i] == 'r');
            int isYellow = (leaves[i] == 'y');
            dp[i][0] = dp[i - 1][0] + isYellow;
            dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + isRed;
            if (i >= 2)
            {
                dp[i][2] = std::min(dp[i - 1][1], dp[i - 1][2]) + isYellow;
            }
        }

        return dp[n - 1][2];
    }
};

class Solution3
{
public:
    struct Status
    {
        int leftRed;
        int centerYellow;
        int rightRed;
    };

    int minimumOperations(std::string leaves)
    {
        // dp[i][j]:对leaves[0:i]进行调整操作，并且第i片叶子处于状态j时的最小操作次数
        // j = 0:第i片叶子是前面的红色部分
        // j = 1:第i片叶子是中间的黄色部分
        // j = 2:第i片叶子是后面的红色部分
        Status dp;

        // 初始化，考虑前3片叶子的情况
        dp.leftRed = (leaves[0] == 'y') + (leaves[1] == 'y') + (leaves[2] == 'y');
        dp.centerYellow = std::min((leaves[0] == 'y') + (leaves[1] == 'r') + (leaves[2] == 'r'),
                                   (leaves[0] == 'y') + (leaves[1] == 'y') + (leaves[2] == 'r'));
        dp.rightRed = (leaves[0] == 'y') + (leaves[1] == 'r') + (leaves[2] == 'y');

        for (int i = 3; i < leaves.size(); ++i)
        {
            Status last(dp);
            dp.leftRed = last.leftRed + (leaves[i] == 'y');
            dp.centerYellow = std::min(last.leftRed, last.centerYellow) + (leaves[i] == 'r');
            dp.rightRed = std::min(last.centerYellow, last.rightRed) + (leaves[i] == 'y');
        }

        return dp.rightRed;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

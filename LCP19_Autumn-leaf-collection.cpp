#include <iostream>
#include <vector>

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

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

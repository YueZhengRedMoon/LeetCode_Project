#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxMatrixSum(std::vector<std::vector<int>>& matrix)
    {
        long long ans = 0;
        int negCnt = 0;         // matrix中负数元素的个数
        int maxNeg = INT_MIN;   // 最大的负数
        int minPos = INT_MAX;   // 最小的正数
        bool hasZero = false;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                int x = matrix[i][j];

                if (x < 0)
                {
                    ans -= x;
                    ++negCnt;
                    if (x > maxNeg)
                    {
                        maxNeg = x;
                    }
                }
                else if (x > 0)
                {
                    ans += x;
                    if (x < minPos)
                    {
                        minPos = x;
                    }
                }
                else    // x == 0
                {
                    hasZero = true;
                }
            }
        }

        if (hasZero || negCnt % 2 == 0)
        {
            return ans;
        }
        else
        {
            return ans - 2 * std::min(-maxNeg, minPos);
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
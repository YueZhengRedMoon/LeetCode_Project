#include <iostream>
#include <vector>

class Solution
{
public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        long long sum = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                sum += grid[i][j];
            }
        }

        if (sum % 2)    // 矩阵元素和是奇数，无法分割成元素和相等的两部分
        {
            return false;
        }

        std::vector<long long> colSum(n, 0);
        long long upSum = 0, leftSum = 0, half = sum / 2;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                long long x = grid[i][j];
                colSum[j] += x;
                upSum += x;

                if (j == n - 1 && upSum == half)
                {
                    return true;
                }
                if (i == m - 1)
                {
                    leftSum += colSum[j];
                    if (leftSum == half)
                    {
                        return true;
                    }
                    else if (leftSum > half)
                    {
                        return false;
                    }
                }
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
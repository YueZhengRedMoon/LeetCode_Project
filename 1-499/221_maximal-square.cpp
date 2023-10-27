#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

class Solution
{
public:
    int maximalSquare(std::vector<std::vector<char>> &matrix)
    {
        int row = matrix.size(), col = matrix[0].size();
        // dp[i][j]:以matrix[i][j]为右下角的只包含1的最大正方形的边长
        std::vector<std::vector<int>> dp(row, std::vector<int>(col, 0));

        int ans = 0;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    dp[i][j] = 1;
                    if (i >= 1 && j >= 1 && dp[i - 1][j - 1] > 0)
                    {
                        for (int k = 1; k <= dp[i - 1][j - 1] && i >= k && j >= k; ++k)
                        {
                            if (matrix[i][j - k] == '1' && matrix[i - k][j] == '1')
                            {
                                ++dp[i][j];
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    if (dp[i][j] > ans)
                    {
                        ans = dp[i][j];
                    }
                }
            }
        }

        return ans * ans;
    }
};

class Solution2
{
public:
    int maximalSquare(std::vector<std::vector<char>> &matrix)
    {
        int row = matrix.size(), col = matrix[0].size();
        // dp[i][j]:以matrix[i][j]为右下角的只包含1的最大正方形的边长
        std::vector<std::vector<int>> dp(row, std::vector<int>(col, 0));

        int ans = 0;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    if (i >= 1 && j >= 1)
                    {
                        dp[i][j] = std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                    }
                    else
                    {
                        dp[i][j] = 1;
                    }
                    if (dp[i][j] > ans)
                    {
                        ans = dp[i][j];
                    }
                }
            }
        }

        return ans * ans;
    }
};

class Solution3
{
public:
    int maximalSquare(std::vector<std::vector<char>> &matrix)
    {
        int ans = 0;
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::bitset<MAX_N>> binaryMatrix(m);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    binaryMatrix[i][j] = true;
                    ans = 1;
                }
            }
        }

        for (int i = 0; i < m; ++i)
        {
            std::bitset<MAX_N> andVal(binaryMatrix[i]);
            for (int j = i + 1; j < m; ++j)
            {
                andVal &= binaryMatrix[j];
                int width = getContinueOneCount(andVal);
                int height = j - i + 1;
                if (width < height)
                {
                    break;
                }
                if (height > ans)
                {
                    ans = height;
                }
            }
        }

        return ans * ans;
    }

private:
    static constexpr int MAX_N = 300;

    int getContinueOneCount(std::bitset<MAX_N> num)
    {
        int count = 0;
        while (num.any())
        {
            num &= (num << 1);
            ++count;
        }
        return count;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

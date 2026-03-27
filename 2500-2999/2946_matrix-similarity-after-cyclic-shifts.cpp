#include <iostream>
#include <vector>

class Solution
{
public:
    bool areSimilar(std::vector<std::vector<int>>& mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        std::vector<std::vector<int>> mat2(m, std::vector<int>(n));
        k %= n;
        for (int i = 0; i < m; ++i)
        {
            int delta = k;
            if (i % 2 == 0)  // 偶数行左移
            {
                delta = -delta;
            }

            for (int j = 0; j < n; ++j)
            {
                mat2[i][(j + delta + n) % n] = mat[i][j];
            }
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] != mat2[i][j])
                    return false;
            }
        }
        return true;
    }
};

class Solution2
{
public:
    bool areSimilar(std::vector<std::vector<int>>& mat, int k)
    {
        // 如果一行左移k次等于自己，那么其右移k次，也能等于自己
        int n = mat[0].size();
        for (const std::vector<int>& row : mat)
        {
            for (int j = 0; j < n; ++j)
            {
                if (row[j] != row[(j + k) % n])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
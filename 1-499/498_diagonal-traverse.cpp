#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size();
        std::vector<int> ans;
        ans.reserve(m * n);
        int i = 0, j = 0, di = -1, dj = 1;
        while (!(i == m - 1 && j == n - 1))
        {
            ans.push_back(mat[i][j]);
            i += di;
            j += dj;

            if (j >= n)
            {
                j = n - 1;
                i += 2;
                di = 1;
                dj = -1;
            }
            if (i < 0)
            {
                i = 0;
                di = 1;
                dj = -1;
            }
            if (i >= m)
            {
                i = m - 1;
                j += 2;
                di = -1;
                dj = 1;
            }
            if (j < 0)
            {
                j = 0;
                di = -1;
                dj = 1;
            }
        }
        ans.push_back(mat[m - 1][n - 1]);
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

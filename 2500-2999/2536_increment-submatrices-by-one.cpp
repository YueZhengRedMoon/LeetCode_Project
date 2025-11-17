#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> rangeAddQueries(int n, std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<int>> ans(n, std::vector<int>(n, 0));
        for (const std::vector<int>& q : queries)
        {
            int row1 = q[0], col1 = q[1], row2 = q[2], col2 = q[3];
            for (int r = row1; r <= row2; ++r)
            {
                ++ans[r][col1];
                if (col2 + 1 < n)
                    --ans[r][col2 + 1];
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                ans[i][j] += ans[i][j - 1];
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
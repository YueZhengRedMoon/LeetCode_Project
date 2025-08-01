#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        std::vector<std::vector<int>> ans(numRows);
        ans[0] = {1};
        for (int i = 1; i < numRows; ++i)
        {
            ans[i].resize(i + 1);
            ans[i][0] = 1;
            for (int j = 1; j < i; ++j)
                ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
            ans[i][i] = 1;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

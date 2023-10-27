#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> reconstructMatrix(int upper, int lower, std::vector<int> &colsum)
    {
        int n = colsum.size();
        std::vector<std::vector<int>> ans(2, std::vector<int>(n, 0));
        for (int i = 0; i < n && upper >= 0 && lower >= 0; ++i)
        {
            if (colsum[i] == 2)
            {
                ans[0][i] = ans[1][i] = 1;
                --upper;
                --lower;
            }
            else if (colsum[i] == 1)
            {
                if (upper > lower)
                {
                    ans[0][i] = 1;
                    --upper;
                }
                else
                {
                    ans[1][i] = 1;
                    --lower;
                }
            }
        }
        if (upper != 0 || lower != 0)
            return {};
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
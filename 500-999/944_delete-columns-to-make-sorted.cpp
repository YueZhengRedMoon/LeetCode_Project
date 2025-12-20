#include <iostream>
#include <vector>

class Solution
{
public:
    int minDeletionSize(std::vector<std::string>& strs)
    {
        int ans = 0, n = strs.size(), m = strs[0].size();
        for (int j = 0; j < m; ++j)
        {
            for (int i = 1; i < n; ++i)
            {
                if (strs[i][j] < strs[i - 1][j])
                {
                    ++ans;
                    break;
                }
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
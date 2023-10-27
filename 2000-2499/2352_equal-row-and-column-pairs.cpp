#include <iostream>
#include <vector>
#include <map>

class Solution
{
public:
    int equalPairs(std::vector<std::vector<int>> &grid)
    {
        int n = grid.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int equal = 1;
                for (int k = 0; k < n; ++k)
                {
                    if (grid[i][k] != grid[k][j])
                    {
                        equal = 0;
                        break;
                    }
                }
                ans += equal;
            }
        }
        return ans;
    }
};

class Solution2
{
    int equalPairs(std::vector<std::vector<int>> &grid)
    {
        // std::vector<int>不可哈希，所以不能使用unordered_map
        // 由于std::vector<int>可以通过 < 来比较，所以可以使用基于红黑树排序的map
        std::map<std::vector<int>, int> count;
        for (const auto &row : grid)
        {
            ++count[row];
        }

        int n = grid.size();
        int ans = 0;
        for (int j = 0; j < n; ++j)
        {
            std::vector<int> col(n);
            for (int i = 0; i < n; ++i)
            {
                col[i] = grid[i][j];
            }
            auto it = count.find(col);
            if (it != count.end())
            {
                ans += it->second;
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
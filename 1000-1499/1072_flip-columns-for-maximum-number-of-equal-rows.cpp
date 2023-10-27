#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int maxEqualRowsAfterFlips(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::unordered_map<std::bitset<MAX_N>, int> map;
        for (int i = 0; i < m; ++i)
        {
            std::bitset<MAX_N> zero, one;
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    one[j] = true;
                }
                else
                {
                    zero[j] = true;
                }
            }
            ++map[one];
            ++map[zero];
        }
        int ans = 0;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            ans = std::max(ans, it->second);
        }
        return ans;
    }

private:
    static constexpr int MAX_N = 300;
};

class Solution2
{
public:
    int maxEqualRowsAfterFlips(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::unordered_map<std::bitset<MAX_N>, int> count;
        for (int i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 1)
            {
                std::transform(matrix[i].begin(), matrix[i].end(), matrix[i].begin(), [](int value) {return 1 - value;});
            }
            std::bitset<MAX_N> pattern;
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    pattern.set(j);
                }
            }
            ++count[pattern];
        }
        int ans = 0;
        for (auto it = count.begin(); it != count.end(); ++it)
        {
            ans = std::max(it->second, ans);
        }
        return ans;
    }

private:
    static constexpr int MAX_N = 300;
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
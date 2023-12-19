#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> findPeakGrid(std::vector<std::vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        int lower = 0, upper = m - 2;
        while (lower <= upper)
        {
            int i = (lower + upper) / 2;
            int j = indexOfMax(mat[i]);
            if (mat[i][j] > mat[i + 1][j])
            {
                upper = i - 1;
            }
            else    // mat[i][j] < mat[i + 1][j]
            {
                lower = i + 1;
            }
        }
        return {lower, indexOfMax(mat[lower])};
    }

private:
    int indexOfMax(const std::vector<int> &nums)
    {
        return std::max_element(nums.begin(), nums.end()) - nums.begin();
    }
};
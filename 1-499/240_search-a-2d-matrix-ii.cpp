#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int m = matrix.size();
        int mid;
        int up = 0, down = m;
        while (up < down)
        {
            mid = (up + down) >> 1;
            if (matrix[mid][0] >= target)
            {
                down = mid;
            }
            else
            {
                // matrix[mid][0] < target
                up = mid + 1;
            }
        }

        if (up != m && matrix[up][0] == target)
            return true;

        for (int i = up - 1; i >= 0; --i)
        {
            if (std::binary_search(matrix[i].begin(), matrix[i].end(), target))
                return true;
        }

        return false;
    }
};

class Solution2
{
public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int r = 0, c = n - 1;
        while (r < m && c >= 0)
        {
            if (matrix[r][c] > target)
                --c;
            else if (matrix[r][c] < target)
                ++r;
            else
                return true;
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

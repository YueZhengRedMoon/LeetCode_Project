#include <iostream>
#include <vector>

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int left1 = 0, right1 = m - 1, index = -1;
        // 找到最大的小于等于target的matrix[i][0]
        while (left1 <= right1)
        {
            int mid1 = (left1 + right1) >> 1;
            if (matrix[mid1][0] <= target)
            {
                index = mid1;
                left1 = mid1 + 1;
            }
            // matrix[mid1][0] > target
            else
            {
                right1 = mid1 - 1;
            }
        }
        if (index != -1)
        {
            int left2 = 0, right2 = n - 1;
            while (left2 <= right2)
            {
                int mid2 = (left2 + right2) >> 1;
                if (matrix[index][mid2] > target)
                {
                    right2 = mid2 - 1;
                }
                else if (matrix[index][mid2] < target)
                {
                    left2 = mid2 + 1;
                }
                else
                {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 13;
    bool ans = solution.searchMatrix(matrix, target);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
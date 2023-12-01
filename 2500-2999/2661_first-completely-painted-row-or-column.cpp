#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int firstCompleteIndex(std::vector<int> &arr, std::vector<std::vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        std::unordered_map<int, std::pair<int, int>> indices;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                indices[mat[i][j]] = {i, j};
            }
        }

        int ans = 0x3f3f3f3f, arrSize = arr.size();
        std::vector<int> row(m, n), col(n, m);
        for (int k = 0; k < arrSize; ++k)
        {
            auto &[i, j] = indices[arr[k]];
            --row[i];
            --col[j];
            if (row[i] == 0 || col[j] == 0)
            {
                ans = k;
                break;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

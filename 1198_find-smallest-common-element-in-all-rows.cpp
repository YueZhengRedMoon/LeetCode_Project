#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int smallestCommonElement(std::vector<std::vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        std::vector<int> minIndex(m, 0);
        bool maxMinUpdated = true;
        int maxMin;
        while (maxMinUpdated)
        {
            maxMinUpdated = false;
            maxMin = mat[0][minIndex[0]];
            for (int i = 1; i < m; ++i)
            {
                if (mat[i][minIndex[i]] > maxMin)
                {
                    maxMin = mat[i][minIndex[i]];
                    maxMinUpdated = true;
                }
                else if (mat[i][minIndex[i]] < maxMin)
                {
                    maxMinUpdated = true;
                }
            }

            if (maxMinUpdated)
            {
                for (int i = 0; i < m; ++i)
                {
                    if (mat[i][minIndex[i]] != maxMin)
                    {
                        auto it = std::lower_bound(mat[i].begin() + minIndex[i], mat[i].end(), maxMin);
                        if (it == mat[i].end())
                            return -1;
                        minIndex[i] = it - mat[i].begin();
                    }
                }
            }
        }

        return maxMin;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>

class Solution
{
public:
    int findLonelyPixel(std::vector<std::vector<char>> &picture)
    {
        int m = picture.size(), n = picture[0].size();
        std::vector<int> row(m), col(n);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (picture[i][j] == 'B')
                {
                    ++row[i];
                    ++col[j];
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            if (row[i] != 1)
                continue;

            for (int j = 0; j < n; ++j)
            {
                if (picture[i][j] == 'B' && col[j] == 1)
                    ++ans;
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

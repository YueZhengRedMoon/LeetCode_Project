#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<char>> rotateTheBox(std::vector<std::vector<char>>& boxGrid)
    {
        int m = boxGrid.size(), n = boxGrid[0].size();
        for (int i = 0; i < m; ++i)
        {
            int start = 0, stoneCnt = 0, emptyCnt = 0;
            bool move = false;
            for (int j = 0; j < n; ++j)
            {
                if (boxGrid[i][j] == '#')   // 石头
                {
                    ++stoneCnt;
                }
                else if (boxGrid[i][j] == '.')  // 空白
                {
                    ++emptyCnt;
                    if (stoneCnt)
                    {
                        move = true;
                    }
                }

                if (boxGrid[i][j] == '*' || j == n - 1)
                {
                    if (move)
                    {
                        for (int k = start; k < start + emptyCnt; ++k)
                        {
                            boxGrid[i][k] = '.';
                        }
                        for (int k = start + emptyCnt; k < start + emptyCnt + stoneCnt; ++k)
                        {
                            boxGrid[i][k] = '#';
                        }
                    }
                    start = j + 1;
                    move = false;
                    stoneCnt = 0;
                    emptyCnt = 0;
                }
            }
        }

        std::vector<std::vector<char>> ans(n, std::vector<char>(m));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ans[j][m - 1 - i] = boxGrid[i][j];
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
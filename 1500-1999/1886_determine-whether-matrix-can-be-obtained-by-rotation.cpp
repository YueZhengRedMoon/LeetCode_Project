#include <iostream>
#include <vector>

class Solution
{
public:
    bool findRotation(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& target)
    {
        int n = mat.size();
        int ok = (1 << 4) - 1;  // bool ok[4] = {true, true, true, true}
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int x = mat[i][j];
                if (x != target[i][j])
                {
                    ok &= ~(1 << 0);    // ok[0] = false;
                }
                if (x != target[j][n - 1 - i])
                {
                    ok &= ~(1 << 1);    // ok[1] = false;
                }
                if (x != target[n - 1 - i][n - 1 - j])
                {
                    ok &= ~(1 << 2);    // ok[2] = false;
                }
                if (x != target[n - 1 - j][i])
                {
                    ok &= ~(1 << 3);    // ok[3] = false;
                }
                if (ok == 0)    // 所有ok[i]都是false
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
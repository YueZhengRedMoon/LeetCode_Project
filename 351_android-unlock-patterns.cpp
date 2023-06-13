#include <iostream>
#include <unordered_set>

class Solution
{
public:
    int numberOfPatterns(int m, int n)
    {
        initPass();
        atLeastPassed = m;
        ans = 0;
        backtracking(n, 0, 0, 0);
        return ans;
    }

private:
    int pass[10][10]{0};
    int atLeastPassed;
    int ans;
    std::unordered_set<std::string> patterns;

    void backtracking(int remain, int passed, int from, int visited)
    {
        if (passed >= atLeastPassed)
        {
            ++ans;
        }
        if (remain == 0)
        {
            return;
        }

        visited |= (1 << from);
        for (int to = 1; to <= 9; ++to)
        {
            if (visited & (1 << to)) continue;
            if (!pass[from][to] || ((1 << pass[from][to]) & visited))
            {
                backtracking(remain - 1, passed + 1, to, visited | (1 << pass[from][to]));
            }
        }
    }

    void initPass()
    {
        pass[1][3] = pass[3][1] = 2;
        pass[1][7] = pass[7][1] = 4;
        pass[1][9] = pass[9][1] = 5;
        pass[2][8] = pass[8][2] = 5;
        pass[3][7] = pass[7][3] = 5;
        pass[3][9] = pass[9][3] = 6;
        pass[4][6] = pass[6][4] = 5;
        pass[7][9] = pass[9][7] = 8;
    }
};

int main()
{
    Solution solution;
    int m = 1, n = 2;
    int ans = solution.numberOfPatterns(m, n);
    std::cout << ans << std::endl;
    return 0;
}
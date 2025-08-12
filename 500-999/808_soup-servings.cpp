#include <iostream>
#include <vector>

class Solution
{
public:
    double soupServings(int n)
    {
        if (n >= 4451)
            return 1;

        n = (n + 24) / 25;
        memo = std::vector<std::vector<double>>(n + 1, std::vector<double>(n + 1));
        return dfs(n, n);
    }

    double dfs(int a, int b)
    {
        if (a <= 0 && b <= 0)
        {
            // a和b同时取完，取概率的一半
            return 0.5;
        }
        if (a <= 0) // 此时b > 0
        {
            return 1;
        }
        if (b <= 0) // 此时a > 0
        {
            return 0;
        }

        double& res = memo[a][b];
        if (res == 0)   // 没有计算过
        {
            res = (dfs(a - 4, b) + dfs(a - 3, b - 1) + dfs (a - 2, b - 2) + dfs(a - 1, b - 3)) / 4.0;
        }
        return res;
    }

private:
    std::vector<std::vector<double>> memo;
};

int main()
{
    Solution solution;
    int n = 1;
    double p = 0;
    while (true)
    {
        p = solution.soupServings(n);
        if (p >= 1.0 - 1e-5)
        {
            std::cout << "n = " << n << ", p = " << p << std::endl;
            break;
        }
        ++n;
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int count(std::string num1, std::string num2, int minSum, int maxSum)
    {
        int ans = count(num2, minSum, maxSum) - count(num1, minSum, maxSum) + MOD;
        int sum = 0;
        for (char c : num1)
            sum += c - '0';
        ans += (minSum <= sum && sum <= maxSum);
        return ans % MOD;
    }

private:
    const int MOD = 1e9 + 7;

    // 返回[0, num]中minSum <= digit_sum(x) <= maxSum的x的数量
    int count(std::string num, int minSum, int maxSum)
    {
        int n = num.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(std::min(n * 9, maxSum) + 1, -1));
        std::function<int(int, int, bool)> dfs = [&](int i, int sum, bool isLimit) -> int {
            if (sum > maxSum)
                return 0;
            if (i == n)
                return sum >= minSum;
            if (!isLimit && memo[i][sum] != -1)
                return memo[i][sum];

            int up = isLimit ? num[i] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= up; ++d)
            {
                res = (res + dfs(i + 1, sum + d, isLimit && (d == up))) % MOD;
            }

            if (!isLimit)
                memo[i][sum] = res;

            return res;
        };
        return dfs(0, 0, true);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

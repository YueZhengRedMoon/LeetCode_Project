#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    std::vector<int> distributeCandies(int candies, int n)
    {
        std::vector<int> ans(n);
        // n^2 * x^2 + (2 * n^2 + n) * x + (n^2 + n - 2 * candies) = 0
        // a = n^2, b = (2 * n^2 + n), c = (n^2 + n - 2 * candies)
        long long a = n * n, b = 2 * n * n + n, c = n * n + n - 2LL * candies;
        long long x = std::max((long long) std::floor(((-b + std::sqrt(b * b - 4LL * a * c)) / (2LL * a))), -1LL);
        if (x >= 0)
        {
            for (int i = 0; i < n; ++i)
            {
                ans[i] = (x * (x + 1) / 2) * n + (i + 1) * (x + 1);
                candies -= ans[i];
            }
        }
        long long y = std::min<long long>((x + 1) * n + 1, candies);
        for (int i = 0; i < n && candies > 0; ++i)
        {
            ans[i] += y;
            candies -= y;
            y = std::min<long long>(y + 1, candies);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

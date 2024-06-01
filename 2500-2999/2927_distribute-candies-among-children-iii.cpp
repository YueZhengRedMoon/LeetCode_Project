#include <iostream>
#include <vector>

class Solution
{
public:
    long long distributeCandies(int n, int limit)
    {
        long long k1 = std::min(n, limit), k2 = std::max(0, n - limit), k3 = std::max(0, n - 2 * limit), ans = 0;
        if (k1 >= k2)
        {
            long long m = k1 - k2 + 1LL;
            ans = m * (n + 1LL) - ((k2 + k1) * m / 2LL);
        }
        k2 = std::min(k1, k2 - 1);
        if (k2 >= k3)
        {
            long long m = k2 - k3 + 1;
            ans += ((k3 + k2) * m / 2LL) + m * (2LL * limit - n + 1LL);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    int n = 5, limit = 2;
    long long ans = solution.distributeCandies(n, limit);
    std::cout << ans << std::endl;
    return 0;
}

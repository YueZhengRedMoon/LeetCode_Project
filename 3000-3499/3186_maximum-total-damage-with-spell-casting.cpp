#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    long long maximumTotalDamage(std::vector<int>& power)
    {
        std::unordered_map<int, int> cnt;
        for (int x : power)
        {
            ++cnt[x];
        }

        std::vector<std::pair<int, int>> a(cnt.begin(), cnt.end());
        std::sort(a.begin(), a.end());

        int n = a.size();
        std::vector<long long> f(n + 1);
        for (int i = 0, j = 0; i < n; ++i)
        {
            auto& [x, c] = a[i];
            while (a[j].first < x - 2)
                ++j;

            f[i + 1] = std::max(f[i], f[j] + (long long) x * c);
        }
        return f[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

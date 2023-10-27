#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int sumDistance(std::vector<int> &nums, std::string s, int d)
    {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i)
        {
            a[i] = (long long) nums[i] + (s[i] == 'R' ? d : -d);
        }
        std::sort(a.begin(), a.end());

        long long ans = 0, sum = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = (ans + i * a[i] - sum) % MOD;
            sum += a[i];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

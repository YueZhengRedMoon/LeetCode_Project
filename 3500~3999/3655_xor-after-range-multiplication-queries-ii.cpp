#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    int xorAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        int n = nums.size();
        int B = std::sqrt(queries.size());
        std::vector<std::vector<int>> diff(B);

        for (const std::vector<int>& q : queries)
        {
            int l = q[0], r = q[1], k = q[2];
            long long v = q[3];
            if (k < B)
            {
                if (diff[k].empty())
                {
                    diff[k].resize(n + k, 1);
                }
                diff[k][l] = diff[k][l] * v % MOD;
                r = r - (r - l) % k + k;
                diff[k][r] = diff[k][r] * pow(v, MOD - 2) % MOD;
            }
            else
            {
                for (int i = l; i <= r; i += k)
                {
                    nums[i] = nums[i] * v % MOD;
                }
            }
        }

        for (int k = 1; k < B; ++k)
        {
            if (diff[k].empty())
            {
                continue;
            }
            for (int start = 0; start < k; ++start)
            {
                long long mulD = 1;
                for (int i = start; i < n; i += k)
                {
                    mulD = mulD * diff[k][i] % MOD;
                    nums[i] = nums[i] * mulD % MOD;
                }
            }
        }

        int ans = 0;
        for (int x : nums)
        {
            ans ^= x;
        }
        return ans;
    }

private:
    static constexpr int MOD = 1'000'000'007;

    long long pow(long long x, int n)
    {
        long long res = 1;
        while (n)
        {
            if (n % 2)
            {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n /= 2;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
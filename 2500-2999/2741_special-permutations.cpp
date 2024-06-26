#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

namespace WrongAnswer
{
    class Solution
    {
    public:
        int specialPerm(std::vector<int>& nums)
        {
            int n = nums.size();
            std::unordered_map<int, int> bitsetCounter;
            std::function<void(int, int)> dfs = [&](int num, int used) {
                for (int i = 0; i < n; ++i)
                {
                    if ((used & (1 << i)) == 0 && ((nums[i] % num == 0) || (num % nums[i] == 0)))
                    {
                        int newUsed = used | (1 << i);
                        if (used)
                            ++bitsetCounter[newUsed];
                        dfs(nums[i], newUsed);
                    }
                }
            };
            dfs(1, 0);

            const int MOD = 1'000'000'007;
            long long factorial[15] = {1, 1};
            for (int i = 2; i <= n; ++i)
                factorial[i] = factorial[i - 1] * i % MOD;

            long long ans = 0;
            std::vector<std::pair<int, int>> bitsets(bitsetCounter.begin(), bitsetCounter.end());
            std::function<void(int, int, std::vector<int>&)> dfs2 = [&](int i, int set, std::vector<int>& cnts) {
                if (set == (1 << n) - 1)
                {
                    long long res = factorial[cnts.size()];
                    for (int cnt : cnts)
                    {
                        res = res * cnt % MOD;
                    }
                    ans = (ans + res) % MOD;
                    return;
                }
                for (int j = i; j < bitsets.size(); ++j)
                {
                    if ((set & bitsets[j].first) == 0)
                    {
                        cnts.push_back(bitsets[j].second);
                        dfs2(j + 1, set | bitsets[j].first, cnts);
                        cnts.pop_back();
                    }
                }
            };
            std::vector<int> cnts;
            cnts.reserve(n);
            dfs2(0, 0, cnts);
            return ans;
        }
    };
}

class Solution
{
public:
    int specialPerm(std::vector<int>& nums)
    {
        int n = nums.size(), u = (1 << n) - 1;
        std::vector<std::vector<long long>> memo(u, std::vector<long long>(n, -1)); // -1表示没计算过
        std::function<long long(int, int)> dfs = [&](int s, int i) -> long long
        {
            if (s == 0)
                return 1;   // 找到一个特别的排列
            long long& res = memo[s][i];
            if (res != -1)
                return res;

            res = 0;
            for (int j = 0; j < n; ++j)
            {
                if (((s >> j) & 1) && (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0))
                {
                    res += dfs(s ^ (1 << j), j);
                }
            }
            return res;
        };
        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += dfs(u ^ (1 << i), i);
        }
        return ans % 1'000'000'007;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {20,100,50,5,10,70,7};
    int ans = solution.specialPerm(nums);
    std::cout << ans << std::endl;
    return 0;
}

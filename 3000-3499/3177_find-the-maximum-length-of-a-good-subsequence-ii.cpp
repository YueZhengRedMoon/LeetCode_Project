#include <iostream>
#include <vector>
#include <unordered_map>
#include "debug.h"

namespace TimeLimit
{
    class Solution
    {
    public:
        int maximumLength(std::vector<int>& nums, int maxEqual)
        {
            int n = nums.size(), ans = 1;
            // f[i][k]:nums[0, i]中以nums[i]结尾，
            // 且存在k个下标有seq[i] == seq[i+1]的好序列的最长长度，等于-1则表示不存在这样的好序列
            std::vector<std::vector<int>> f(n + 1, std::vector<int>(maxEqual + 1, -1));
            f[0][0] = 0;

            for (int i = 1; i <= n; ++i)
            {
                for (int k = 0; k <= maxEqual; ++k)
                {
                    for (int j = ans; j < i; ++j)
                    {
                        if (nums[j - 1] == nums[i - 1])
                        {
                            f[i][k] = std::max(f[i][k], f[j][k] + 1);
                        }
                        else if (k)
                        {
                            f[i][k] = std::max(f[i][k], f[j][k - 1] + 1);
                        }
                    }
                    if (f[i][k] > ans)
                        ans = f[i][k];
                }
            }

            return ans;
        }
    };
}

class Solution
{
public:
    int maximumLength(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, std::vector<int>> fs;
        std::vector<std::array<int, 3>> records(k + 1);
        for (int x : nums)
        {
            auto& f = fs[x];
            f.resize(k + 1);
            for (int j = k; j >= 0; --j)
            {
                ++f[j];
                if (j)
                {
                    auto& r = records[j - 1];
                    int mx = r[0], mx2 = r[1], num = r[2];
                    f[j] = std::max(f[j], (x != num ? mx : mx2) + 1);
                }

                // records[j]维护fs[.][j]的mx, mx2, num
                int v = f[j];
                auto& p = records[j];
                if (v > p[0])
                {
                    if (x != p[2])
                    {
                        p[2] = x;
                        p[1] = p[0];
                    }
                    p[0] = v;
                }
                else if (x != p[2] && v > p[1])
                {
                    p[1] = v;
                }
            }
        }

        return records[k][0];
    }
};

class Solution2
{
public:
    int maximumLength(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, std::vector<int>> fs;
        std::vector<int> mx(k + 2);
        for (int x : nums)
        {
            auto& f = fs[x];
            f.resize(k + 1);
            for (int j = k; j >= 0; --j)
            {
                f[j] = std::max(f[j], mx[j]) + 1;
                mx[j + 1] = std::max(mx[j + 1], f[j]);
            }
        }
        return mx[k + 1];
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,2,1,1,3};
    int k = 2;
    int ans = solution.maximumLength(nums, k);
    std::cout << ans << std::endl;
    return 0;
}

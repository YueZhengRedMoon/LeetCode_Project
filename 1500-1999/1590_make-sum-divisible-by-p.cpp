#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minSubarray(std::vector<int>& nums, int p)
    {
        int n = nums.size();

        // s[i]:nums[0, i)的和 MOD p
        std::vector<int> s(n + 1, 0);
        for (int i = 0; i < n; ++i)
        {
            s[i + 1] = (s[i] + nums[i]) % p;
        }

        int x = s[n];
        if (x == 0)
        {
            return 0;
        }

        int ans = n;
        std::unordered_map<int, int> last;
        for (int i = 0; i <= n; ++i)
        {
            last[s[i]] = i;
            auto it = last.find((s[i] - x + p) % p);
            if (it != last.end())
            {
                ans = std::min(ans, i - it->second);
            }
        }
        return ans < n ? ans : -1;
    }
};

class Solution2
{
public:
    int minSubarray(std::vector<int>& nums, int p)
    {
        int n = nums.size(), sumModP = 0;   // sumModP：前缀和MOD P的值
        std::unordered_map<int, std::vector<int>> indices; // indices[r]:前缀和sum(nums[0,i]) mod p = r的所有下标
        for (int i = 0; i < n; ++i)
        {
            sumModP = (sumModP + nums[i]) % p;
            indices[sumModP].push_back(i);
        }

        // nums的所有元素和恰好能被p整除，无需移除子数组
        if (sumModP == 0)
        {
            return 0;
        }

        int ans = n;

        // 特殊考虑移除最短后缀的情况
        auto it = indices.find(0);
        if (it != indices.end())
        {
            ans = n - it->second.back() - 1;
        }

        // 枚举保留nums[j, n)，加上最长有多长的前缀，可以使元素和能被p整除
        for (int j = n - 1, suffix = 0; j > 0; --j)
        {
            suffix = (suffix + nums[j]) % p;
            int prefix = (p - suffix) % p;

            // 特殊情况，将前缀nums[0, j)全部移除
            if (suffix == 0)
            {
                ans = std::min(ans, j);
            }

            it = indices.find(prefix);
            if (it != indices.end())
            {
                const std::vector<int>& idxList = it->second;
                // 通过二分查找，查找最大的下标i，有sum(nums[0,i]) % p == prefix，且i < j
                int i = -1, l = 0, r = idxList.size();
                while (l < r)
                {
                    int mid = (l + r) / 2;
                    if (idxList[mid] < j)
                    {
                        i = idxList[mid];
                        l = mid + 1;
                    }
                    else    // idxList[mid] >= j
                    {
                        r = mid;
                    }
                }

                if (i != -1)
                {
                    // nums[i + 1, j - 1]被移除
                    ans = std::min(ans, j - i - 1);
                }
            }
        }

        return ans == n ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
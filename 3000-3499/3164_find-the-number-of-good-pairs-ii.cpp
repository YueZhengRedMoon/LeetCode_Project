#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    // nums1[i]能被nums2[j]*k整除，等价于nums1[i]是k的倍数，且nums1[i]/k能被nums2[j]整除
    // 即nums1[i]/k有一个因子d等于nums2[j]

    long long numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        std::unordered_map<int, int> cnt;
        for (int x : nums1)
        {
            if (x % k)
                // x不能整除k，x不可能作为优质数对的一部分
                continue;

            x /= k;
            for (int d = 1; d * d <= x; ++d)    // 枚举因子
            {
                if (x % d)
                {
                    // d不是x的因子
                    continue;
                }

                ++cnt[d];   // 统计因子个数
                if (d * d < x)
                {
                    ++cnt[x / d];
                }
            }
        }

        long long ans = 0;
        for (int x : nums2)
        {
            auto it = cnt.find(x);
            if (it != cnt.end())
                ans +=  it->second;
        }
        return ans;
    }
};

class Solution2
{
public:
    long long numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        std::unordered_map<int, int> cnt1;
        for (int x : nums1)
        {
            if (x % k == 0)
                ++cnt1[x / k];
        }
        if (cnt1.empty())
            return 0;

        std::unordered_map<int, int> cnt2;
        for (int x : nums2)
        {
            ++cnt2[x];
        }

        long long ans = 0;
        int u = 0;
        for (auto it = cnt1.begin(); it != cnt1.end(); ++it)
        {
            if (it->first > u)
                u = it->first;
        }
        for (auto it = cnt2.begin(); it != cnt2.end(); ++it)
        {
            int x = it->first, cnt = it->second;
            int s = 0;
            for (int y = x; y <= u; y += x) // 枚举x的倍数
            {
                s += cnt1.find(y) != cnt1.end() ? cnt1[y] : 0;
            }
            ans += (long long) s * cnt;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

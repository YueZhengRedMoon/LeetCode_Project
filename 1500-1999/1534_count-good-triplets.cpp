#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int countGoodTriplets(std::vector<int>& arr, int a, int b, int c)
    {
        int ans = 0, n = arr.size();
        for (int i = 0; i < n - 2; ++i)
        {
            for (int j = i + 1; j < n - 1; ++j)
            {
                for (int k = j + 1; k < n; ++k)
                {
                    if (std::abs(arr[i] - arr[j]) <= a && std::abs(arr[j] - arr[k]) <= b && std::abs(arr[i] - arr[k]) <= c)
                    {
                        ++ans;
                    }
                }
            }
        }
        return ans;
    }
};

// 没看懂
class Solution2
{
public:
    int countGoodTriplets(std::vector<int>& arr, int a, int b, int c)
    {
        int n = arr.size(), mx = *std::max_element(arr.begin(), arr.end()), ans = 0;
        std::vector<int> s(mx + 2);
        for (int j = 0; j < n; ++j)
        {
            int jv = arr[j];
            for (int k = j + 1; k < n; ++k)
            {
                int kv = arr[k];
                if (std::abs(jv - kv) > b)
                    continue;

                int l = std::max({jv - a, kv - c, 0});
                int r = std::min({jv + a, kv + c, mx});
                ans += std::max(s[r + 1] - s[l], 0);
            }
            for (int v = jv + 1; v < mx + 2; ++v)
                ++s[v];
        }
        return ans;
    }
};

class Solution3
{
public:
    int countGoodTriplets(std::vector<int>& arr, int a, int b, int c)
    {
        int n = arr.size(), ans = 0;

        // idx:arr的下标数组，将idx按照arr[idx[i]]的值排序
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int i, int j) {return arr[i] < arr[j];});

        for (int j : idx)
        {
            int jv = arr[j];

            // 找出满足i < j，且|arr[i]-arr[j]| <= a的所有arr[i]，保存到left中
            std::vector<int> left;
            for (int i : idx)
            {
                int iv = arr[i];
                if (i < j && std::abs(iv - jv) <= a)
                    left.push_back(iv);
            }

            // 找出满足j < k，且|arr[j]-arr[k]| <= b的所有arr[k]，保存到right中
            std::vector<int> right;
            for (int k : idx)
            {
                int kv = arr[k];
                if (j < k && std::abs(jv - kv) <= b)
                    right.push_back(kv);
            }

            // 遍历left中的iv，在right中找有多少个kv满足|iv-kv|<=c
            int k1 = 0, k2 = 0;
            for (int iv : left)
            {
                while (k2 < right.size() && right[k2] <= iv + c)
                    ++k2;
                while (k1 < right.size() && right[k1] < iv - c)
                    ++k1;

                // right[k1] >= iv - c，right[k2] > iv + c
                ans += k2 - k1;
            }
        }

        return ans;
    }
};

int main()
{
    Solution3 solution;
    std::vector<int> arr = {3, 0, 1, 1, 9, 7};
    int a = 7, b = 2, c = 3;
    int ans = solution.countGoodTriplets(arr, a, b, c);
    std::cout << ans << std::endl;
    return 0;
}

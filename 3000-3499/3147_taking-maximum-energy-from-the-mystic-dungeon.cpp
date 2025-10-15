#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class Solution
{
public:
    int maximumEnergy(std::vector<int>& energy, int k)
    {
        int ans = INT_MIN, n = energy.size();
        std::vector<int> f(n);  // f[i]:到达i处能吸收的最大能量
        for (int i = 0; i < n; ++i)
        {
            f[i] = energy[i];
            if (i >= k)
                f[i] = std::max(f[i], f[i - k] + energy[i]);

            if (i >= n - k && f[i] > ans)
                ans = f[i];
        }

        return ans;
    }
};

class Solution2
{
public:
    int maximumEnergy(std::vector<int>& energy, int k)
    {
        int n = energy.size(), ans = INT_MIN;
        for (int i = n - k; i < n; ++i) // 枚举终点
        {
            int sufSum = 0;
            for (int j = i; j >= 0; j -= k)
            {
                sufSum += energy[j];
                if (sufSum > ans)
                    ans = sufSum;
            }
        }
        return ans;
    }
};

class Solution3
{
public:
    int maximumEnergy(std::vector<int>& energy, int k)
    {
        int n = energy.size();
        for (int i = n - k - 1; i >= 0; --i)
        {
            energy[i] += energy[i + k];
        }
        return *std::max_element(energy.begin(), energy.end());
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
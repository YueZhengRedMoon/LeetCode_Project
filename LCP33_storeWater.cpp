#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

class Solution
{
public:
    int storeWater(std::vector<int> &bucket, std::vector<int> &vat)
    {
        int ans = 0;
        int n = bucket.size();
        int maxMinStoreCount = 0;  // 将一个水桶的容量升级到最优后，最多需要的蓄水次数

        for (int i = 0; i < n; ++i)
        {
            if (vat[i] == 0) continue;
            if (bucket[i] == 0)
            {
                ++bucket[i];
                ++ans;
            }

            int minStoreCount = calcStoreCount(vat[i], bucket[i]);
            int minOpCount = minStoreCount;
            if (minStoreCount < maxMinStoreCount)
            {
                continue;
            }
            double x = sqrt(vat[i]) - bucket[i];
            int x1 = static_cast<int>(floor(x));
            int x2 = static_cast<int>(ceil(x));
            if (x1 > 0)
            {
                int storeCount = calcStoreCount(vat[i], bucket[i] + x1);
                if (storeCount + x1 < minOpCount)
                {
                    minOpCount = storeCount + x1;
                    minStoreCount = storeCount;
                }
            }
            if (x2 > 0)
            {
                int storeCount = calcStoreCount(vat[i], bucket[i] + x2);
                if (storeCount + x2 < minOpCount)
                {
                    minStoreCount = std::min(minStoreCount, storeCount);
                }
            }
            if (minStoreCount > maxMinStoreCount)
            {
                maxMinStoreCount = minStoreCount;
            }
        }

        for (int i = 0; i < n; ++i)
        {
            if (vat[i] == 0) continue;
            int size = (vat[i] / maxMinStoreCount) + (vat[i] % maxMinStoreCount == 0 ? 0 : 1);
            if (size > bucket[i])
            {
                ans += size - bucket[i];
            }
        }

        return ans + maxMinStoreCount;
    }

private:
    /** 对于最低蓄水量为v水缸，容量为b的水桶，最少要倒多少次水 */
    inline int calcStoreCount(int v, int b)
    {
        return (v / b) + (v % b == 0 ? 0 : 1);
    }
};

class Solution2
{
public:
    int storeWater(std::vector<int> &bucket, std::vector<int> &vat)
    {
        int maxK = *std::max_element(vat.begin(), vat.end());
        if (maxK == 0) return 0;
        int ans = std::numeric_limits<int>::max();
        int n = bucket.size();
        for (int k = 1; k <= maxK && k < ans; ++k)
        {
            int temp = 0;
            for (int i = 0; i < n; ++i)
            {
                temp += std::max(0, (vat[i] + k - 1) / k - bucket[i]);
            }
            ans = std::min(ans, temp + k);
        }
        return ans;
    }
};

class Solution3
{
public:
    int storeWater(std::vector<int> &bucket, std::vector<int> &vat)
    {
        int ans = 0;
        int n = bucket.size();
        int maxMinStoreCount = 0;
        for (int i = 0; i < n; ++i)
        {
            if (vat[i] == 0) continue;
            if (bucket[i] == 0)
            {
                ++bucket[i];
                ++ans;
            }

            // int x = static_cast<int>((vat[i] - bucket[i] * bucket[i]) / static_cast<double>(bucket[i]));
            int x = (vat[i] - bucket[i] * bucket[i]) / bucket[i];
            if (x > 0)
            {
                maxMinStoreCount = std::max(maxMinStoreCount, calcStoreCount(vat[i], bucket[i] + x));
            }
            else
            {
                maxMinStoreCount = std::max(maxMinStoreCount, calcStoreCount(vat[i], bucket[i]));
            }
        }

        for (int i = 0; i < n; ++i)
        {
            if (vat[i] == 0) continue;
            int size = (vat[i] / maxMinStoreCount) + (vat[i] % maxMinStoreCount == 0 ? 0 : 1);
            if (size > bucket[i])
            {
                ans += size - bucket[i];
            }
        }

        return ans + maxMinStoreCount;
    }

private:
    /** 对于最低蓄水量为v水缸，容量为b的水桶，最少要倒多少次水 */
    inline int calcStoreCount(int v, int b)
    {
        return (v / b) + (v % b == 0 ? 0 : 1);
    }
};

int main()
{
    Solution solution;
    std::vector<int> bucket1 = {9, 0, 1};
    std::vector<int> vat1 = {0, 2, 2};
    int ans1 = solution.storeWater(bucket1, vat1);
    std::cout << ans1 << std::endl;
    return 0;
}
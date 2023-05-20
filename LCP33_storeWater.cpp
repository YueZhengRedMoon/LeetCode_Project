#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    int storeWater(std::vector<int> &bucket, std::vector<int> &vat)
    {
        int n = bucket.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (bucket[i] == 0 && vat[i] != 0)
            {
                ++bucket[i];
                ++ans;
            }
        }

        int maxCount = 0;   // 记录最多的倒水次数
        for (int i = 0; i < n; ++i)
        {
            if (vat[i] == 0) continue;

            // 对于每个水桶，计算其扩容几次后可以使得总操作次数最少
            int deltaX = 0; // 扩充的容量
            int minCount = calcCount(vat[i], bucket[i]);  // 对于水桶i最少需要操作几次
            if (minCount <= maxCount)
            {
                continue;
            }
            double x = sqrt(vat[i]) - bucket[i];
            int x1 = static_cast<int>(x);
            int x2 = x1 + 1;
            if (x1 > 0)
            {
                int count = calcCount(vat[i], bucket[i] + x1);
                if (count + x1 < minCount)
                {
                    deltaX = x1;
                    minCount = count + x1;
                }
            }
            if (x2 > 0)
            {
                int count = calcCount(vat[i], bucket[i] + x2);
                if (count + x2 < minCount)
                {
                    deltaX = x2;
                    minCount = count + x2;
                }
            }
            bucket[i] += deltaX;
            ans += deltaX;
            maxCount = std::max(maxCount, minCount - deltaX);
        }

        ans += maxCount;
        return ans;
    }

private:
    inline int calcCount(double v, double b)
    {
        return static_cast<int>(ceil(v / b));
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
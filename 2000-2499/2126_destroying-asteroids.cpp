#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool asteroidsDestroyed(int mass, std::vector<int>& asteroids)
    {
        long long massSum = mass;
        std::sort(asteroids.begin(), asteroids.end());
        for (int m : asteroids)
        {
            if (massSum >= m)
            {
                massSum += m;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};

class Solution2
{
public:
    // 一个>=2^k的数，加上另一个>=2^k的数，和一定>=2^(k+1)
    // 将小行星按照质量分组，质量在[2^i,2^(i+1))的小行星分到同一组
    // 设行星质量为massSum，如果massSum>=组内的最小值，则massSum加上组内最小值后，结果一定大于组内的每个值，该组质量可以全部加到massSum

    bool asteroidsDestroyed(int mass, std::vector<int>& asteroids)
    {
        int maxWidth = bitWidth(*std::max_element(asteroids.begin(), asteroids.end()));
        std::vector<int> min(maxWidth, INT_MAX);    // min[i]:asteroids中，值在[2^i,2^(i+1))中的最小值
        std::vector<long long> sum(maxWidth);   // sum[i]:asteroids在，值在[2^i,2^(i+1))中的所有元素的和

        for (int m : asteroids)
        {
            int i = bitWidth(m) - 1;
            if (m < min[i])
            {
                min[i] = m;
            }
            sum[i] += m;
        }

        long long massSum = mass;
        for (int i = 0; i < maxWidth; ++i)
        {
            if (min[i] == INT_MAX)
            {
                continue;
            }
            if (massSum < min[i])   // 无法摧毁这组的任意小行星
            {
                return false;
            }
            massSum += sum[i];  // 获得这组小行星的质量
        }
        return true;
    }

private:
    int bitWidth(int n)
    {
        return 32 - __builtin_clz(n);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
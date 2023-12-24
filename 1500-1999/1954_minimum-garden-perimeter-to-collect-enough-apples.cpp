#include <iostream>
#include <cmath>

class Solution
{
public:
    long long minimumPerimeter(long long neededApples)
    {
        long long ans = neededApples, lower = 0, upper = neededApples;
        while (lower <= upper)
        {
            long long mid = lower + (upper - lower) / 2;
            if (appleCount(mid) >= neededApples)
            {
                ans = 8 * mid;
                upper = mid - 1;
            }
            else
            {
                lower = mid + 1;
            }
        }
        return ans;
    }

private:
    // 计算左上角(-x,x)，左下角(-x,-x)，右上角(x,x)和右下角(x,-x)的正方形中的苹果树
    long long appleCount(long long x)
    {
        long long y = x * (x + 1) / 2;  // 0+1+2+...+x
        // 2*(x+1)*y:左上角(0,x)，左下角(0,0)，右上角(1,1)和右下角(1,0)的正方形中的苹果树
        // -4*y:去除重合的边上的苹果数
        return 8 * (x + 1) * y - 4 * y; // 等价于2*x*(x+1)*(2*x+1)
    }
};

class Solution2
{
public:
    long long minimumPerimeter(long long neededApples)
    {
        long long n = std::cbrt(neededApples / 4.0);
        if (2 * n * (n + 1) * (2 * n + 1) < neededApples)
            ++n;
        return 8 * n;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

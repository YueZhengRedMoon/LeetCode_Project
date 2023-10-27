#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumTastiness(std::vector<int> &price, int k)
    {
        std::sort(price.begin(), price.end());
        // 二分枚举糖果任意两个糖果之间价格绝对差的最小值
        int left = 0, right = price.back() - price.front();
        while (left < right)
        {
            int mid = (left + right + 1) >> 1;
            // 可以取出k类糖果，使得任意两个糖果的最小价格绝对差都 >= mid
            if (check(price, k, mid))
            {
                // 最小价格绝对差还有上升空间，增大绝对差的最小值
                left = mid;
            }
            // 不能取出k类糖果，使得任意两个糖果的最小价格绝对差都 >= mid
            else
            {
                // 预估的最小价格绝对差太大了，降低它
                right = mid  - 1;
            }
        }
        return left;
    }

private:
    bool check(const std::vector<int> &price, int k, int tastiness)
    {
        int prev = -0x3f3f3f3f;
        int count = 0;
        for (const int &p : price)
        {
            if (p - prev >= tastiness)
            {
                if (++count >= k)
                {
                    return true;
                }
                prev = p;
            }

        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
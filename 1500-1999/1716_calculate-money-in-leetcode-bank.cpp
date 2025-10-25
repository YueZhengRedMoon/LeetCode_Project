#include <iostream>
#include <vector>

class Solution
{
public:
    int totalMoney(int n)
    {
        // 第x周存的钱= (x+(x+6)) * 7 / 2 = 7*x+21
        // 从第1周到第x周存的钱 = (7*1+21) + (7*2+21) + ... + (7*x+21) = 7*(1+2+...+x) + 21*x = 7*(1+x)*x/2 + 21*x
        // 如果最后一周是第y周，且只存了z天，则存的钱=(y+0)+(y+1)+...+(y+z-1) = z * y + (z-1)*z/2
        int x = n / 7;
        int y = x + 1;
        int z = n % 7;

        return 7 * (1 + x) * x / 2 + 21 * x + z * y + (z - 1) * z / 2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
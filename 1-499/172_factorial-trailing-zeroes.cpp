#include <iostream>
#include <vector>

class Solution
{
public:
    // 思想：因为以2为因子的数一定比以5为因子的数多，统计以5, 25, 125, 625...为因子的数的数量，累加起来即为答案
    // 以5为因子的数会贡献1个尾随0
    // 以25为因子的数总共会贡献2个尾随0，其中1个尾随0在统计以5为因子的数时被算上
    // 以125为因子的数总共会贡献3个尾随0，其中第1个尾随0在统计以5为因子的数时被算上，第2个尾随0在统计以25为因子的数时被算上
    // ...

    int trailingZeroes(int n)
    {
        int ans = 0;
        int x = 5;
        while (x <= n)
        {
            ans += n / x;
            x *= 5;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> singleNumber(std::vector<int> &nums)
    {
        // 假设只出现一次的两个数是x1和x2，则xorSum == x1 ^ x2
        int xorSum = 0;
        for (int num : nums)
        {
            xorSum ^= num;
        }

        // 找到一个x1和x2对应二进制位不同的位lsb，基于lsb将nums中的数分类
        // 获取异或和的二进制表示中最低位的1所表示的数
        int lsb = (xorSum == INT_MIN ? xorSum : xorSum & (-xorSum));    // 防止移除，(INT_MIN)2 == 1000...0

        // 对于nums中的每一个数，基于其二进制表示的lsb位是1还是0将其分类
        // 对于所有出现次数为2次的数，这个数一定在同一类中
        // 对于两个出现次数为1次的数，它们一定在不同的类中
        // 将这两个类中的所有数异或，即可得到x1和x2
        int type1 = 0, type2 = 0;
        for (int num : nums)
        {
            if (num & lsb)
            {
                type1 ^= num;
            }
            else
            {
                type2 ^= num;
            }
        }

        return {type1, type2};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

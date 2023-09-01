#include <iostream>
#include <vector>

class Solution
{
public:
    long long waysToBuyPensPencils(int total, int cost1, int cost2)
    {
        if (cost1 < cost2)
            std::swap(cost1, cost2);

        long long ans = 0;
        for (int i = 0; i <= total; i += cost1) // 枚举购买一种笔花费的钱
        {
            int pencilNum = (total - i) / cost2;    // 剩下的钱最多可以购买的另一种笔的数量
            ans += pencilNum + 1;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

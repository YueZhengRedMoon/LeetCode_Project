#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfWays(std::string corridor)
    {
        int n = corridor.size();
        constexpr int MOD = 1'000'000'007;
        int cntP = 0;   // 每两个座椅右边有多少珠植物
        int cntS = 0;
        long long ans = 1;
        for (int i = 0; i < n; ++i)
        {
            if (corridor[i] == 'S') // 椅子
            {
                if (cntS == 2)  // 新的一组座椅
                {
                    ans = (ans * (cntP + 1ll)) % MOD;
                    cntS = 1;
                    cntP = 0;
                }
                else
                {
                    ++cntS;
                }
            }
            else    // corridor[i] == 'P', 植物
            {
                if (cntS == 2)
                {
                    ++cntP;
                }
            }
        }
        // 没有椅子或者椅子的数量是奇数，无法使每一段恰好有2个座位
        if (cntS <= 1)
        {
            return 0;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumAddedCoins(std::vector<int>& coins, int target)
    {
        std::sort(coins.begin(), coins.end());
        int ans = 0, s = 1, i = 0, n = coins.size();   // 已经可以得到[0, s-1]中的所有整数
        while (s <= target)
        {
            // 遍历到整数x=coins[i]，由于已经可以得到[0, s-1]中的所有整数，将其中的所有整数都加x就可以得到[x, s+x-1]中的所有整数
            if (i < n && coins[i] <= s)
            {
                // 如果x<=s，就可以得到[0, s+x-1]在的所有整数
                s += coins[i++];
            }
            // 遍历完了coins数组，或x > s，意味着无法得到s，将s加入到数组中，就可以得到[0, 2s-1]中的所有整数
            else
            {
                s <<= 1;    // [0, 2s)中的所有整数都已经可以获得
                ++ans;      // 添加了s
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

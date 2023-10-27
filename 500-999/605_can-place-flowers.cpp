#include <iostream>
#include <vector>
#include "../debug.h"

class Solution
{
public:
    bool canPlaceFlowers(std::vector<int> &flowerbed, int n)
    {
        int cnt = 0, size = flowerbed.size();
        for (int i = 0; i < size && cnt < n; ++i)
        {
            if (flowerbed[i] == 0)
            {
                if ((i > 0 && flowerbed[i - 1] == 1) || (i + 1 < size && flowerbed[i + 1] == 1))
                    continue;

                flowerbed[i] = 1;
                ++cnt;
                logObj(i);
            }
        }
        return cnt == n;
    }
};

int main()
{
    Solution solution;
    std::vector<int> flowerbed = {1,0,0,0,0,1};
    int n = 2;
    bool ans = solution.canPlaceFlowers(flowerbed, n);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}

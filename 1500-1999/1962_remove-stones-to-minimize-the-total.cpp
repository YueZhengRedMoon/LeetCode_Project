#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int minStoneSum(std::vector<int> &piles, int k)
    {
        int n = piles.size();
        std::make_heap(piles.begin(), piles.end(), std::less<>());  // 原地化大顶堆
        while (k-- && piles[0])
        {
            int top = piles[0];
            std::pop_heap(piles.begin(), piles.end());
            piles[n - 1] = (top + 1) / 2;   // (top/2)向上取整
            std::push_heap(piles.begin(), piles.end());
        }
        return std::accumulate(piles.begin(), piles.end(), 0);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

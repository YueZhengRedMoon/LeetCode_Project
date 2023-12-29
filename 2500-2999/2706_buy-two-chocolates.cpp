#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int buyChoco(std::vector<int> &prices, int money)
    {
        std::nth_element(prices.begin(), prices.begin() + 1, prices.end());
        int spend = prices[0] + prices[1];
        return spend <= money ? money - spend : money;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

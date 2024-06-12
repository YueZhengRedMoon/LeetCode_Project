#include <iostream>
#include <vector>

class Solution
{
public:
    int accountBalanceAfterPurchase(int purchaseAmount)
    {
        if (purchaseAmount % 10 >= 5)
            return 100 - (purchaseAmount + 9) / 10 * 10;
        else
            return 100 - purchaseAmount / 10 * 10;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

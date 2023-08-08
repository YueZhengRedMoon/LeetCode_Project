#include <iostream>
#include <vector>

class Solution
{
public:
    int subtractProductAndSum(int n)
    {
        int product = 1, sum = 0;
        while (n)
        {
            int t = n % 10;
            n /= 10;
            product *= t;
            sum += t;
        }
        return product - sum;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
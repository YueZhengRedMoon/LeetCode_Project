#include <iostream>
#include <vector>

class Solution
{
public:
    int sumOfTheDigitsOfHarshadNumber(int x)
    {
        int n = x, sum = 0;
        while (n)
        {
            sum += n % 10;
            n /= 10;
        }
        return x % sum == 0 ? sum : -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

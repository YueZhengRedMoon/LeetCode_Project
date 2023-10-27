#include <iostream>
#include <vector>

class Solution
{
public:
    bool isArmstrong(int n)
    {
        unsigned int sum = 0, temp = n, k = std::to_string(n).size();
        while (temp && sum <= n)
        {
            sum += pow(temp % 10, k);
            temp /= 10;
        }
        return sum == n;
    }

private:
    unsigned int pow(unsigned int a, unsigned int k)
    {
        if (a == 0)
            return 0;

        unsigned int res = 1;
        while (k)
        {
            if (k & 1)
                res *= a;
            a *= a;
            k >>= 1;
        }

        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
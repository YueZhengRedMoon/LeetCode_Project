#include <iostream>
#include <vector>

class Solution
{
public:
    double myPow(double x, int n)
    {
        if (x == 1.0)
        {
            return x;
        }

        double ans = 1.0;
        if (n > 0)
        {
            while (n)
            {
                if (n & 1)
                    ans *= x;
                x *= x;
                n >>= 1;
            }
        }
        else if (n < 0)
        {
            long long absN = -(long long)n;
            while (absN)
            {
                if (absN & 1)
                    ans /= x;
                x *= x;
                absN >>= 1;
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

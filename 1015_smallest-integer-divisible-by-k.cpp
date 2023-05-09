#include <iostream>
#include <vector>

class Solution
{
public:
    int smallestRepunitDivByK(int k)
    {
        if (k % 2 == 0 || k % 5 == 0)
        {
            return -1;
        }

        // n % k = reside != 0
        // new_n = n * 10 + 1
        // new_reside = new_n % k = (n * 10 + 1) % k = (n * 10 % k + 1 % k) % k = (10 * reside + 1 % k) % k
        int reside = 1 % k, len = 1;
        while (reside != 0) // 当且仅当k % 2 == 0或k % 5 == 0时，余数才不可能为0
        {
            reside = (10 * reside + 1) % k;
            ++len;
        }

        return len;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>

class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0 || x > 0 && x % 10 == 0)
        {
            return false;
        }

        int rev = 0;
        while (rev < x / 10)
        {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        return rev == x || rev == x / 10;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

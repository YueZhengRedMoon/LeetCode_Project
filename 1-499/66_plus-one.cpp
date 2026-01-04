#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> plusOne(std::vector<int>& digits)
    {
        int n = digits.size();
        int carry = 1;
        for (int i = n - 1; i >= 0 && carry; --i)
        {
            if (++digits[i] == 10)
            {
                digits[i] = 0;
            }
            else
            {
                carry = 0;
            }
        }

        if (carry)
        {
            std::vector<int> ans(n + 1, 0);
            ans[0] = 1;
            return ans;
        }

        return digits;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
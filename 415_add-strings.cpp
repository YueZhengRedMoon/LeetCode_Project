#include <iostream>
#include <vector>

class Solution
{
public:
    std::string addStrings(std::string num1, std::string num2)
    {
        int len1 = num1.size(), len2 = num2.size();
        if (len1 < len2)
        {
            std::swap(num1, num2);
            std::swap(len1, len2);
        }

        int i = len1 - 1, j = len2 - 1, carry = 0;
        while (j >= 0)
        {
            int val = ctoi(num1[i]) + ctoi(num2[j]) + carry;
            carry = val / 10;
            num1[i] = itoc(val % 10);
            --i;
            --j;
        }
        while (i >= 0 && carry)
        {
            int val = ctoi(num1[i]) + carry;
            carry = val / 10;
            num1[i] = itoc(val % 10);
            --i;
        }

        if (carry)
        {
            num1 = std::string({itoc(carry)}) + num1;
        }
        return num1;
    }

private:
    inline int ctoi(char c)
    {
        return c - '0';
    }

    inline char itoc(int i)
    {
        return i + '0';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
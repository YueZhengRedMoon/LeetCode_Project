#include <iostream>
#include <vector>

class Solution
{
public:
    bool isPalindrome(std::string s)
    {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            while (left < right && !isalnum(s[left]))
                ++left;

            while (left < right && !isalnum(s[right]))
                --right;

            if (left == right)
                return true;

            if (tolower(s[left]) == tolower(s[right]))
            {
                ++left;
                --right;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
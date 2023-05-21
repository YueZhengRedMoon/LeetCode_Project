#include <iostream>
#include <vector>

class Solution
{
public:
    std::string makeSmallestPalindrome(std::string s)
    {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            if (s[left] < s[right])
            {
                s[right] = s[left];
            }
            else
            {
                s[left] = s[right];
            }
            ++left;
            --right;
        }
        return s;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

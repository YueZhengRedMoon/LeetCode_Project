#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfSpecialChars(std::string word)
    {
        int lowercase[26] = {0}, uppercase[26] = {0};
        for (char c : word)
        {
            if (c >= 'a')
            {
                uppercase[c - 'a'] = true;
            }
            else
            {
                lowercase[c - 'A'] = true;
            }
        }
        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (lowercase[i] && uppercase[i])
            {
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
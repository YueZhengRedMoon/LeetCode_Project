#include <iostream>
#include <string>

class Solution
{
public:
    bool isSubsequence(std::string s, std::string t)
    {
        if (s.empty())
        {
            return true;
        }

        for (int i = 0, j = 0; i < t.size(); ++i)
        {
            if (t[i] == s[j])
            {
                ++j;
            }
            if (j == s.size())
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
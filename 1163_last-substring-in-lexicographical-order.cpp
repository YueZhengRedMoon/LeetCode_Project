#include <iostream>
#include <vector>

class Solution
{
public:
    std::string lastSubstring(std::string s)
    {
        int i = 0, j = 1, n = s.size();
        while (j < n)
        {
            int k = 0;
            while (j + k < n && s[i + k] == s[j + k])
            {
                ++k;
            }
            if (j + k < n && s[i + k] < s[j + k])
            {
                int t = i;
                i = j;
                j = std::max(j + 1, t + k + 1);
            }
            // s[i + k] > s[j + k]
            else
            {
                j = j + k + 1;
            }
        }
        return s.substr(i, n - i);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

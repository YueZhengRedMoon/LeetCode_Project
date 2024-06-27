#include <iostream>
#include <vector>

class Solution
{
public:
    std::string smallestString(std::string s)
    {
        int n = s.size(), lastA = -1;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == 'a')
            {
                if (i - lastA > 1)
                {
                    for (int j = lastA + 1; j < i; ++j)
                    {
                        --s[j];
                    }
                    return s;
                }
                lastA = i;
            }
        }
        for (int i = std::min(lastA + 1, n - 1); i < n; ++i)
        {
            s[i] = s[i] == 'a' ? 'z' : s[i] - 1;
        }
        return s;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

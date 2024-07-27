#include <iostream>
#include <vector>

class Solution
{
public:
    std::string getSmallestString(std::string s, int k)
    {
        int n = s.size();
        for (int i = 0; i < n && k; ++i)
        {
            int d1 = s[i] - 'a';        // s[i]减至'a'的距离
            int d2 = 'z' - s[i] + 1;    // s[i]增至'a'的距离
            if (d1 <= d2)
            {
                int d = std::min(d1, k);
                s[i] -= d;
                k -= d;
            }
            else    // d1 > d2
            {
                if (k < d2)
                {
                    s[i] -= k;
                    k = 0;
                }
                else
                {
                    s[i] = 'a';
                    k -= d2;
                }
            }
        }
        return s;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

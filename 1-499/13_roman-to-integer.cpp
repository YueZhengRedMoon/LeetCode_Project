#include <iostream>

class Solution
{
public:
    int romanToInt(std::string s)
    {
        int ans = 0;
        int i = 0;
        int len = s.size();
        while (i < len)
        {
            switch (s[i])
            {
                case 'I':
                    if (i < len - 1 && (s[i + 1] == 'V' || (s[i + 1] == 'X')))
                    {
                        ans += s[i + 1] == 'V' ? 4 : 9;
                        ++i;
                    }
                    else
                    {
                        ++ans;
                    }
                    break;
                case 'V':
                    ans += 5;
                    break;
                case 'X':
                    if (i < len - 1 && (s[i + 1] == 'L' || (s[i + 1] == 'C')))
                    {
                        ans += s[i + 1] == 'L' ? 40 : 90;
                        ++i;
                    }
                    else
                    {
                        ans += 10;
                    }
                    break;
                case 'L':
                    ans += 50;
                    break;
                case 'C':
                    if (i < len - 1 && (s[i + 1] == 'D' || (s[i + 1] == 'M')))
                    {
                        ans += s[i + 1] == 'D' ? 400 : 900;
                        ++i;
                    }
                    else
                    {
                        ans += 100;
                    }
                    break;
                case 'D':
                    ans += 500;
                    break;
                case 'M':
                    ans += 1000;
                    break;
            }
            ++i;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
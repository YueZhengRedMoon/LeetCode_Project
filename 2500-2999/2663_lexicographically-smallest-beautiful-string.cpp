#include <iostream>
#include <string_view>

class Solution
{
public:
    std::string smallestBeautifulString(std::string s, int alphaLen)
    {
        int n = s.size();
        for (int i = n - 1; i >= 0; --i)
        {
            int idx = s[i] - 'a' + 1;
            while (idx < alphaLen)
            {
                char nc = 'a' + idx;
                if ((i == 0 || s[i - 1] != nc) && (i < 2 || s[i - 2] != nc))    // s[i]可以替换为nc
                {
                    s[i] = nc;
                    char c = 'a';
                    int j = i + 1;
                    if (i > 0 && s[i - 1] == 'a')
                    {
                        if (j < n)
                        {
                            if (s[i] == 'b')
                            {
                                s[j++] = 'c';
                            }
                            else
                            {
                                s[j++] = 'b';
                            }
                        }
                    }
                    else if (i == 0 && s[i] == 'b')
                    {
                        char cc[3] = {'a', 'c', 'b'};
                        j = 1;
                        int k = 0;
                        while (j < n)
                        {
                            s[j++] = cc[k];
                            k = (k + 1) % 3;
                        }
                        return s;
                    }
                    while (j < n)
                    {
                        if (j > 2 && s[j - 2] == c)
                        {
                            if (++c == 'd')
                                c = 'a';
                        }
                        s[j++] = c;
                        if (++c == 'd')
                            c = 'a';
                    }
                    return s;
                }
                ++idx;
            }
        }
        return "";
    }
};

int main()
{
    Solution solution;
    std::string s = "aonmonm";
    int k = 15;
    std::string ans = solution.smallestBeautifulString(s, k);
    std::cout << ans << std::endl;
    return 0;
}

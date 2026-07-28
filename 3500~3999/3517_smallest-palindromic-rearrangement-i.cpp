#include <iostream>
#include <string>

class Solution
{
public:
    std::string smallestPalindrome(std::string s)
    {
        int cnt[26];
        for (char c : s)
        {
            ++cnt[c - 'a'];
        }

        int n = s.size(), k = 0;
        if (n & 1)  // 长度为奇数，将出现次数为奇数的字符放在字符串中间
        {
            for (k = 0; k < 26; ++k)
            {
                if (cnt[k] & 1)
                {
                    s[n / 2] = 'a' + k;
                    --cnt[k];
                    break;
                }
            }
        }

        k = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            while (cnt[k] == 0)
                ++k;

            s[i] = s[j] = 'a' + k;
            cnt[k] -= 2;
        }
        return s;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
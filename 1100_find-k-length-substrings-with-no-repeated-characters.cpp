#include <iostream>
#include <cstring>
#include "debug.h"

class Solution
{
public:
    int numKLenSubstrNoRepeats(std::string s, int k)
    {
        int len = s.size();
        if (k > len)
            return 0;

        int left = 0, right = 0, ans = 0;
        int charIndex[26];
        std::memset(charIndex, -1, sizeof(charIndex));
        while (right <= len)
        {
            int i;
            if (right - left == k)
            {
                // 从滑动窗口中移除s[i]
                i = index(s[left]);
                charIndex[i] = -1;
                ++left;
                ++ans;
            }

            if (right < len)
            {
                i = index(s[right]);
                if (charIndex[i] != -1)
                {
                    // 从滑动窗口中移除所有出现时间比s[right]早的字符
                    for (int &j : charIndex)
                    {
                        if (j < charIndex[i])
                        {
                            j = -1;
                        }
                    }
                    left = charIndex[i] + 1;
                }
                charIndex[i] = right;
            }

            ++right;
        }

        return ans;
    }

private:
    inline int index(char c)
    {
        return c - 'a';
    }
};

int main()
{
    int charIndex[26];
    std::memset(charIndex, -1, sizeof(charIndex));
    debug::printIterRange(std::begin(charIndex), std::end(charIndex));
    return 0;
}

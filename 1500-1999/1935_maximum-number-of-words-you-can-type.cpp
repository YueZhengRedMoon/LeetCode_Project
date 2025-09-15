#include <iostream>
#include <string>

class Solution
{
public:
    int canBeTypedWords(std::string text, std::string brokenLetters)
    {
        int bklBitSet = 0;
        for (char c : brokenLetters)
        {
            bklBitSet |= 1 << index(c);
        }

        int ans = 0;
        int ok = 1;             // 一个单词是否可以完全输入
        for (char c : text)
        {
            if (c == ' ')
            {
                ans += ok;
                ok = 1;
                continue;
            }

            if ((1 << index(c)) & bklBitSet)
            {
                ok = 0;
            }
        }
        ans += ok;

        return ans;
    }

private:
    int index(char c)
    {
        return c - 'a';
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

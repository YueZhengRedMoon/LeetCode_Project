#include <iostream>
#include <string>
#include <cctype>

class Solution
{
public:
    bool detectCapitalUse(std::string word)
    {
        int upperCaseCnt = 0, len = word.size();
        for (char c : word)
        {
            if (std::isupper(c))
                ++upperCaseCnt;
        }
        return upperCaseCnt == len || upperCaseCnt == 0 || (upperCaseCnt == 1 && std::isupper(word[0]));
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

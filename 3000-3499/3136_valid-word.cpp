#include <iostream>

class Solution
{
public:
    bool isValid(std::string word)
    {
        if (word.size() < 3)
            return false;

        bool isContainVowel = false;        // 是否包含元音字母
        bool isContainConsonant = false;    // 是否包含辅音字母
        for (char c : word)
        {
            if (std::isdigit(c))
            {
                continue;
            }
            else if (std::isalpha(c))
            {
                if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U')
                {
                    isContainVowel = true;
                }
                else
                {
                    isContainConsonant = true;
                }
            }
            else
            {
                return false;
            }
        }

        return isContainVowel && isContainConsonant;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

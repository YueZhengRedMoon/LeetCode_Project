#include <iostream>
#include <vector>

class Solution
{
public:
    bool isAcronym(std::vector<std::string> &words, std::string s)
    {
        int wordsSize = words.size(), sLen = s.size();
        if (wordsSize != sLen)
            return false;

        for (int i = 0; i < wordsSize; ++i)
        {
            if (words[i][0] != s[i])
                return false;
        }

        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

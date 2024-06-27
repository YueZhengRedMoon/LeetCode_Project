#include <iostream>
#include <vector>

class Solution
{
public:
    bool validWordAbbreviation(std::string word, std::string abbr)
    {
        int wordLen = word.size(), abbrLen = abbr.size(), i = 0, j = 0;
        while (i < wordLen && j < abbrLen)
        {
            if (std::isdigit(abbr[j]))
            {
                if (abbr[j] == '0')
                    return false;
                int len = abbr[j++] - '0';
                while (j < abbrLen && std::isdigit(abbr[j]))
                {
                    len = len * 10 + (abbr[j++] - '0');
                }
                i += len;
            }
            else
            {
                if (word[i++] != abbr[j++])
                    return false;
            }
        }
        return i == wordLen && j == abbrLen;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

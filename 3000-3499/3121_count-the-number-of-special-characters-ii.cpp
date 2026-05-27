#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfSpecialChars(std::string word)
    {
        std::vector<int> lowercaseIdx(26, -1), uppercaseIdx(26, -1);
        for (int i = 0; i < word.size(); ++i)
        {
            char c = word[i];
            if (c >= 'a')
            {
                lowercaseIdx[c - 'a'] = i;
            }
            else
            {
                if (uppercaseIdx[c - 'A'] == -1)
                {
                    uppercaseIdx[c - 'A'] = i;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (lowercaseIdx[i] != -1 && lowercaseIdx[i] < uppercaseIdx[i])
            {
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
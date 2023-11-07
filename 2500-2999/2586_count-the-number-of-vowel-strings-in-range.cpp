#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int vowelStrings(std::vector<std::string> &words, int left, int right)
    {
        std::function<bool(char)> isVowel = [](char c) -> bool {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        return std::count_if(words.begin() + left, words.begin() + right + 1, [&](const std::string &s) -> bool {
            return isVowel(s.front()) && isVowel(s.back());
        });
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

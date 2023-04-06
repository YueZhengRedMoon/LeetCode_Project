#include <iostream>
#include <vector>
#include <string>

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        std::vector<std::string> combinations;
        if (digits.size() == 0)
        {
            return combinations;
        }
        std::string letters;
        backtracking(digits, 0, combinations, letters);
        return combinations;
    }

private:
    std::string letter[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void backtracking(std::string &digits, int begin, std::vector<std::string> &combinations, std::string letters)
    {
        if (begin == digits.size())
        {
            combinations.push_back(letters);
            return;
        }
        int digit = digits[begin] - '2';
        for (int i = 0; i < letter[digit].size(); ++i)
        {
            backtracking(digits, begin + 1, combinations, letters + letter[digit][i]);
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

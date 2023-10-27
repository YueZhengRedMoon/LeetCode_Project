#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        backtracking(s);
        return combinations;
    }

private:
    std::vector<std::string> combination;
    std::vector<std::vector<std::string>> combinations;

    void backtracking(std::string s)
    {
        if (s.empty())
        {
            combinations.push_back(combination);
        }

        for (int i = 1; i <= s.size(); ++i)
        {
            std::string subStr = s.substr(0, i);
            if (!isPalindrome(subStr))
            {
                continue;
            }
            combination.push_back(subStr);
            backtracking(s.substr(i, s.size()));
            combination.pop_back();
        }
    }

    bool isPalindrome(std::string &s)
    {
        int begin = 0, end = s.size() - 1;
        while (begin < end)
        {
            if (s[begin] != s[end])
            {
                return false;
            }
            ++begin;
            --end;
        }
        return true;
    }
};

int main()
{
    std::string s;
    std::cin >> s;
    Solution solution;
    std::vector<std::vector<std::string>> combinations = solution.partition(s);
    for (auto &combination : combinations)
    {
        for (auto &str : combination)
        {
            std::cout << str << '\t';
        }
        std::cout << std::endl;
    }
    return 0;
}

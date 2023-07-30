#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::string> expand(std::string s)
    {
        std::string word;
        backtracking(s, 0, word);
        std::sort(ans.begin(), ans.end());
        return ans;
    }

private:
    std::vector<std::string> ans;

    void backtracking(const std::string &s, int begin, std::string &word)
    {
        if (begin == s.size())
        {
            ans.push_back(word);
            return;
        }
        if (s[begin] != '{')
        {
            word.push_back(s[begin]);
            backtracking(s, begin + 1, word);
            word.pop_back();
        }
        else
        {
            int end;
            for (end = begin + 1; s[end] != '}'; ++end);
            for (int i = begin + 1; i < end; ++i)
            {
                if (s[i] != ',')
                {
                    word.push_back(s[i]);
                    backtracking(s, end + 1, word);
                    word.pop_back();
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
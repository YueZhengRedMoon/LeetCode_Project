#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> vowelStrings(std::vector<std::string> &words, std::vector<std::vector<int>> &queries)
    {
        int n = words.size();
        std::vector<int> prefix(n + 1,0);
        for (int i = 0; i < n; ++i)
        {
            prefix[i + 1] = prefix[i] + isVowelStr(words[i]);
        }

        std::vector<int> ans;
        ans.reserve(queries.size());
        for (const auto &query : queries)
        {
            int l = query[0], r = query[1] + 1;
            ans.push_back(prefix[r] - prefix[l]);
        }

        return ans;
    }

private:
    inline bool isVowelStr(const std::string &str)
    {
        return isVowel(str.front()) && isVowel(str.back());
    }

    inline bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
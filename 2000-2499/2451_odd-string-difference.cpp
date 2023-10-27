#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    std::string oddString(std::vector<std::string> &words)
    {
        int n = words[0].size();
        std::unordered_map<std::string, int> count;
        for (const auto &word : words)
        {
            std::string diff = getDiff(word, n);
            auto it = count.find(diff);
            if (it == count.end())
            {
                if (!count.empty() && count.begin()->second >= 2)
                {
                    return word;
                }
                else
                {
                    count[diff] = 1;
                }
            }
            else
            {
                ++it->second;
            }
        }
        std::string diff = getDiff(words[0], n);
        if (count[diff] == 1)
            return words[0];
        else
            return words[1];
    }

private:
    std::string getDiff(const std::string &word, int n)
    {
        std::string diff(n - 1, '0');
        for (int i = 0; i <= n - 2; ++i)
        {
            diff[i] = word[i + 1] - word[i] + '0';
        }
        return diff;
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> words = {"wwe","yyg","ssa","ttb","ddd","ssa","xxf","ssa",
                                      "ttb","xxf","xxf","zzh","wwe","yyg","xxf"};
    std::string ans = solution.oddString(words);
    std::cout << ans << std::endl;
    return 0;
}
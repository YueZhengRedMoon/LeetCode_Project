#include <iostream>
#include <vector>
#include <cstring>
#include <string_view>

class Solution
{
public:
    std::vector<std::string> removeAnagrams(std::vector<std::string>& words)
    {
        std::vector<std::string> ans;
        int freq1[26], freq2[26], i = 0;
        countAlphaFreq(words[0], freq1);
        for (int j = 1; j < words.size(); ++j)
        {
            countAlphaFreq(words[j], freq2);
            if (!isAnagrams(words[i], words[j], freq1, freq2))
            {
                ans.push_back(words[i]);
                for (int k = 0; k < 26; ++k)
                    freq1[k] = freq2[k];
                i = j;
            }
        }
        ans.push_back(words[i]);
        return ans;
    }

private:
    void countAlphaFreq(std::string_view word, int freq[26])
    {
        std::memset(freq, 0, sizeof(int) * 26);
        for (char c : word)
        {
            ++freq[c - 'a'];
        }
    }

    bool isAnagrams(std::string_view w1, std::string_view w2, int freq1[26], int freq2[26])
    {
        if (w1.size() != w2.size())
        {
            return false;
        }

        for (int i = 0; i < 26; ++i)
        {
            if (freq1[i] != freq2[i])
                return false;
        }

        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> words = {"abba","baba","bbaa","cd","cd"};
    std::vector<std::string> ans = solution.removeAnagrams(words);
    for (std::string_view word : ans)
    {
        std::cout << word << std::endl;
    }
    return 0;
}

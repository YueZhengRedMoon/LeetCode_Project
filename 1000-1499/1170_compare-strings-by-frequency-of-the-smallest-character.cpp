#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> numSmallerByFrequency(std::vector<std::string> &queries, std::vector<std::string> &words)
    {
        int wordsSize = words.size(), queriesSize = queries.size();
        std::vector<int> freq(wordsSize);
        for (int i = 0; i < wordsSize; ++i)
        {
            freq[i] = f(words[i]);
        }
        std::sort(freq.begin(), freq.end());
        std::vector<int> ans(queriesSize);
        for (int i = 0; i < queriesSize; ++i)
        {
            int count = f(queries[i]);
            ans[i] = freq.end() - std::upper_bound(freq.begin(), freq.end(), count);
        }
        return ans;
    }

private:
    int f(const std::string &word)
    {
        char minChar = word[0];
        int count = 1;
        for (int i = 1; i < word.size(); ++i)
        {
            if (word[i] < minChar)
            {
                minChar = word[i];
                count = 1;
            }
            else if (word[i] == minChar)
            {
                ++count;
            }
        }
        return count;
    }
};

class Solution2
{
public:
    std::vector<int> numSmallerByFrequency(std::vector<std::string> &queries, std::vector<std::string> &words)
    {
        int freq[12] = {0};
        for (const std::string &word : words)
        {
            ++freq[f(word)];
        }
        // 计算后缀和，freq[i]:表示f(w) >= i的单词有多少个
        for (int i = 9; i >= 0; --i)
        {
            freq[i] += freq[i + 1];
        }
        std::vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            int count = f(queries[i]);
            ans[i] = freq[count + 1];
        }
        return ans;
    }

private:
    int f(const std::string &word)
    {
        char minChar = word[0];
        int count = 1;
        for (int i = 1; i < word.size(); ++i)
        {
            if (word[i] < minChar)
            {
                minChar = word[i];
                count = 1;
            }
            else if (word[i] == minChar)
            {
                ++count;
            }
        }
        return count;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
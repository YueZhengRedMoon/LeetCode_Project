#include <iostream>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool equalFrequency(std::string word)
    {
        int frequency[26];
        std::unordered_set<int> set;

        // 枚举删除位置
        for (int i = 0; i < word.size(); ++i)
        {
            std::memset(frequency, 0, sizeof(frequency));
            for (int j = 0; j < word.size(); ++j)
            {
                if (i != j)
                {
                    ++frequency[word[j] - 'a'];
                }
            }
            set.clear();
            for (int j = 0; j < 26; ++j)
            {
                if (frequency[j])
                {
                    set.insert(frequency[j]);
                }
            }
            if (set.size() == 1)
            {
                return true;
            }
        }

        return false;
    }
};

class Solution2
{
public:
    bool equalFrequency(std::string word)
    {
        std::unordered_map<char, int> frequency;
        for (char c : word)
        {
            ++frequency[c];
        }

        std::vector<int> count;
        count.reserve(frequency.size());
        for (auto &[_, c] : frequency)
        {
            count.push_back(c);
        }

        // 字母出现次数从小到大排列
        std::sort(count.begin(), count.end());
        return  count.size() == 1 ||
                count[0] == 1 && std::equal(count.begin() + 2, count.end(), count.begin() + 1) ||
                count.back() == count[count.size() - 2] + 1 && std::equal(count.begin() + 1, count.end() - 1, count.begin());
    }
};

class Solution3
{
public:
    bool equalFrequency(std::string word)
    {
        std::unordered_map<char, int> group;
        for (char c : word)
        {
            ++group[c];
        }

        std::vector<int> frequency;
        frequency.reserve(group.size());
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            frequency.push_back(it->second);
        }

        std::sort(frequency.begin(), frequency.end());
        if (frequency.size() == 1)
        {
            return true;
        }
        else if (frequency[0] == 1 &&
                 std::equal(frequency.begin() + 2, frequency.end(), frequency.begin() + 1))
        {
            return true;
        }
        else if (frequency.back() == frequency[frequency.size() - 2] + 1 &&
                 std::equal(frequency.begin() + 1, frequency.end() - 1, frequency.begin()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
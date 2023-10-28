#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "../debug/debug.h"

class Solution
{
public:
    std::string addBoldTag(std::string s, std::vector<std::string> &words)
    {
        int sLen = s.size(), wordsNum = words.size();
        std::vector<std::vector<int>> next(wordsNum);
        for (int i = 0; i < wordsNum; ++i)
        {
            // 计算next数组
            if (words[i].size() <= sLen)
            {
                calcNext(words[i], next[i]);
            }
        }

        std::vector<std::pair<int, int>> intervals; // 要加粗的区间
        for (int k = 0; k < wordsNum; ++k)
        {
            int wLen = words[k].size(), i = 0;
            while (sLen - i >= wLen)
            {
                int pos = kmp(s, i, words[k], next[k]);
                if (pos == -1)
                    break;

                intervals.emplace_back(pos, pos + wLen - 1);
                i = pos + 1;
            }
        }

        if (intervals.empty())
        {
            return s;
        }

        std::sort(intervals.begin(), intervals.end());
        int begin = intervals[0].first, end = intervals[0].second;
        std::ostringstream oss;
        if (begin > 0)
        {
            oss << substr(s, 0, begin - 1);
        }
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i].first <= end + 1)
            {
                if (intervals[i].second > end)
                {
                    end = intervals[i].second;
                }
            }
            else
            {
                oss << "<b>" << substr(s, begin, end) << "</b>" << substr(s, end + 1, intervals[i].first - 1);
                begin = intervals[i].first;
                end = intervals[i].second;
            }
        }
        oss << "<b>" << substr(s, begin, end) << "</b>";
        if (end + 1 < sLen)
        {
            oss << substr(s, end + 1, sLen - 1);
        }

        return oss.str();
    }

private:
    void calcNext(const std::string &s, std::vector<int> &next)
    {
        int len = s.size();
        next.resize(len);

        // i:后缀的尾部
        // j+1:前缀的尾部，同时也是最长相等前后缀的长度
        // next[i]:s[0:i]的最长相等前后缀的长度-1
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < len; ++i)
        {
            // 前后缀尾部不相同
            while (j >= 0 && s[i] != s[j + 1])
            {
                // 回退j
                j = next[j];
            }
            // 前后缀尾部相同
            if (s[i] == s[j + 1])
            {
                ++j;    // 最长相等前后缀的长度+1
            }
            // 记录s[0:i]的最长相等前后缀的长度
            next[i] = j;
        }
    }

    int kmp(const std::string &s, int sBegin, const std::string &t, const std::vector<int> &next)
    {
        int sLen = s.size(), tLen = t.size();

        int j = -1;
        for (int i = sBegin; i < sLen; ++i)
        {
            // 匹配失败
            while (j >= 0 && s[i] != t[j + 1])
            {
                j = next[j];
            }
            // 匹配成功
            if (s[i] == t[j + 1])
            {
                // 准备判断模式串下一个字符
                ++j;
            }
            // 模式串中所有字符匹配成功
            if (j == tLen - 1)
            {
                return i - tLen + 1;
            }
        }
        // 匹配失败
        return -1;
    }

    inline std::string substr(const std::string &s, int begin, int end)
    {
        int n = end - begin + 1;
        return s.substr(begin, n);
    }
};

int main()
{
    Solution solution;
    std::string s = "aaabbcc";
    std::vector<std::string> words = {"aaa","aab","bc","aaabbcc"};
    std::string ans = solution.addBoldTag(s, words);
    println(ans);
    return 0;
}
#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <sstream>

class Solution
{
public:
    std::string boldWords(std::vector<std::string>& words, std::string s)
    {
        // 获取所有要加粗的索引区间
        std::vector<std::pair<int, int>> boldIntervals;
        for (std::string_view t : words)
        {
            kmp(s, t, boldIntervals);
        }

        // 没有字母被加粗
        if (boldIntervals.empty())
            return s;

        // 排序并合并区间
        std::sort(boldIntervals.begin(), boldIntervals.end());
        std::vector<std::pair<int, int>> mergedIntervals;
        int begin = boldIntervals[0].first, end = boldIntervals[0].second;
        for (int i = 1; i < boldIntervals.size(); ++i)
        {
            int b = boldIntervals[i].first, e = boldIntervals[i].second;
            if (b - end > 1)
            {
                mergedIntervals.emplace_back(begin, end);
                begin = b;
                end = e;
            }
            else    // b - end <= 1
            {
                end = std::max(end, e);
            }
        }
        mergedIntervals.emplace_back(begin, end);

        std::ostringstream oss;
        begin = mergedIntervals[0].first;
        end = mergedIntervals[0].second;
        for (int i = 0, j = 0; i < s.size(); ++i)
        {
            if (i == begin)
            {
                oss << "<b>";
            }
            oss << s[i];
            if (i == end)
            {
                oss << "</b>";
                if (++j < mergedIntervals.size())
                {
                    begin = mergedIntervals[j].first;
                    end = mergedIntervals[j].second;
                }
            }
        }
        return oss.str();
    }

private:
    // 使用kmp算法在源串s中搜索所以的目标串t，并将所有匹配的索引区间添加到boldIntervals中
    void kmp(std::string_view s, std::string_view t, std::vector<std::pair<int, int>>& boldIntervals)
    {
        int sLen = s.size(), tLen = t.size();
        std::vector<int> next(tLen);
        getNext(next, t);
        for (int i = 0, j = -1; i < sLen; ++i)
        {
            while (j >= 0 && s[i] != t[j + 1])
                j = next[j];
            if (s[i] == t[j + 1])
                ++j;
            if (j == tLen - 1)
            {
                boldIntervals.emplace_back(i - tLen + 1, i);
                j = next[j];
            }
        }
    }

    void getNext(std::vector<int>& next, std::string_view s)
    {
        next[0] = -1;
        for (int i = 1, j = -1; i < s.size(); ++i)
        {
            while (j >= 0 && s[i] != s[j + 1])
                j = next[j];
            if (s[i] == s[j + 1])
                ++j;
            next[i] = j;
        }
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> words = {"di","r","buhozb","lofjmyjj","qagllw","zzuid","loyugfh","w","hcfg","ttd",
                                      "vjqigvx","u","mhbivve","x","nzbvyfzx","zs","j","zgtud","zm","huevyex",
                                      "szwigrlwzm","vlrjmobu","b","h","gcmdgyv","anyfelm","vtcejv","myjjzn","jznnj",
                                      "awcxmjn","lw","sju","szszwigrl","eze","ffikvecua","bklrhsju","gyazwel",
                                      "pdhnsxsod","zn","rhsjus","zk","gctgu","vzndt","mfd","jlws","j","zxgaudyo",
                                      "apa","znvixpdh","tgubzczgt"};
    std::string s = "wwcyuaqzgtudmp";
    std::string ans = solution.boldWords(words, s);
    std::cout << ans << std::endl;
    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>

/** 错误 */
class Solution
{
public:
    struct Character
    {
        // 字符的出现范围
        int first;
        int last;
        // 最长子串的起始范围
        int begin;
        int end;
        // 分割点的坐标
        int cutIndex;
    };

    int maxRepOpt1(std::string text)
    {
        Character character[26];
        for (int i = 0; i < 26; ++i)
        {
            character[i].first = character[i].begin = character[i].cutIndex = -1;
            character[i].last = character[i].end = -2;
        }

        auto update = [&](int charIndex, int beginIndex, int endIndex, int cutIndex)
        {
            int len = endIndex - beginIndex + 1;
            if (len > (character[charIndex].end - character[charIndex].begin + 1))
            {
                character[charIndex].begin = beginIndex;
                character[charIndex].end = endIndex;
                character[charIndex].cutIndex = cutIndex;
            }
        };
        int textLen = text.size();
        int curIndex = text[0] - 'a';
        int charIndex = curIndex;   // 当前单字符重复字符串的字符索引
        int start = 0;              // 当前单字符重复字符串的起始下标
        int cutIndex = -1;          // 当前单字符重复字符串分割点的下标
        character[curIndex].first = 0;
        character[curIndex].last = 0;
        for (int i = 1; i < textLen; ++i)
        {
            curIndex = text[i] - 'a';
            character[curIndex].last = i;
            if (character[curIndex].first == -1)
            {
                character[curIndex].first = i;
            }

            if (text[i] != text[i - 1])
            {
                // text[i]可以作为间隔
                if (i + 1 < textLen && text[i - 1] == text[i + 1])
                {
                    // 从start到i-1已经有不同的字符
                    if (cutIndex != -1)
                    {
                        update(charIndex, start, i - 1, cutIndex);
                        start = cutIndex + 1;
                        cutIndex = i;
                    }
                    else
                    {
                        cutIndex = i;
                    }
                    ++i;
                }
                // text[i]不可以作为间隔
                else
                {
                    update(charIndex, start, i - 1, cutIndex);
                    start = i;
                    cutIndex = -1;
                    charIndex = curIndex;
                }
            }
        }
        update(charIndex, start, textLen - 1, cutIndex);

        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            int len = character[i].end - character[i].begin + 1;
            // 有多余字母可以交换
            if (character[i].first < character[i].begin || character[i].last > character[i].end)
            {
                if (character[i].cutIndex == -1)
                {
                    ++len;
                }
            }
            // 没有多余字母可以交换
            else
            {
                if (character[i].cutIndex != -1)    // 需要交换填上间隔
                {
                    --len;
                }
            }

            if (len > ans) ans = len;
        }

        return ans;
    }
};

class Solution2
{
public:
    int maxRepOpt1(std::string text)
    {
        std::unordered_map<char, int> count;    // 每种字符出现的次数
        for (char c : text)
        {
            ++count[c];
        }

        int ans = 0, textLen = text.size();
        for (int i = 0; i < textLen; )
        {
            // 找出当前连续的一段[i, j)
            int j = i;
            while (j < textLen && text[j] == text[i]) ++j;
            int curCnt = j - i; // 当前连续单字符重复子串的长度

            // 如果这一段长度小于该字符出现的总数，并且前面或后面有空位，则表明可以交换，用curCnt+1更新答案
            if (curCnt < count[text[i]] && (j < textLen || i > 0))
            {
                ans = std::max(ans, curCnt + 1);
            }

            // 找到这一段后面与之相隔一个不同字符的另一段[j + 1, k)，如果不存在则k = j + 1
            int k = j + 1;
            while (k < textLen && text[k] == text[i]) ++k;
            // 交换一个字符到j，以连接[i, j)和[j + 1, k)，
            // 如果没有这两个区间以外的字符可以交换，则需要将区间最边上的一个字符换中间来填补
            ans = std::max(ans, std::min(k - i, count[text[i]]));
            i = j;
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::string text("bbababaaaa");
    int ans = solution.maxRepOpt1(text);
    std::cout << ans << std::endl;
    return 0;
}
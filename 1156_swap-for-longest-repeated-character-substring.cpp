#include <iostream>
#include <vector>

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
                if (i + 1 < textLen && (text[i + 1] - 'a') == charIndex)
                {
                    if (cutIndex == -1)
                    {
                        cutIndex = i;
                    }
                    else
                    {
                        update(charIndex, start, i - 1, cutIndex);
                        start = cutIndex + 1;
                        cutIndex = i;
                    }
                    ++i;
                    character[text[i] - 'a'].last = i;
                }
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
            int len = character[i].end - character[i].first + 1;
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

int main()
{
    Solution solution;
    std::string text("bbababaaaa");
    int ans = solution.maxRepOpt1(text);
    std::cout << ans << std::endl;
    return 0;
}
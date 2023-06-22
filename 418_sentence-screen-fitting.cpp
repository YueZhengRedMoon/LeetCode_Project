#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

/** 超时 */
class Solution
{
public:
    int wordsTyping(std::vector<std::string> &sentence, int rows, int cols)
    {
        int ans = 0, curRow = 0, curCol = 0, i = 0, wordNum = sentence.size();
        while (curRow < rows)
        {
            int len = sentence[i].size();
            if (curCol + len <= cols)
            {
                curCol += len + 1;
                ++i;
                if (i == wordNum)
                {
                    i = 0;
                    ++ans;
                }
            }
            else
            {
                ++curRow;
                curCol = 0;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int wordsTyping(std::vector<std::string> &sentence, int rows, int cols)
    {
        int n = sentence.size();
        // prefix[i][j]:显示sentence[i:j]需要多少个格子
        std::vector<std::vector<int>> prefix(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i)
        {
            prefix[i][i] = sentence[i].size();
            for (int j = i + 1; j < n; ++j)
            {
                prefix[i][j] = prefix[i][j - 1] + 1 + sentence[j].size();
            }
        }
        int senLen = prefix[0][n - 1]; // 句子的总长度

        int curRow = 0, remain = cols, ans = 0;
        while (curRow < rows)
        {
            // 这一行剩余的空间可以放下至少一条完整的句子
            if (remain >= senLen)
            {
                int cnt = remain / senLen;  // 这一行剩余的空间可以填充多少条句子
                int blank = cnt - 1;        // 句子之间的空格数
                while (cnt * senLen + blank > remain)
                {
                    --cnt;
                    --blank;
                }
                remain -= cnt * senLen + blank;
                ans += cnt;
                // 句子显示完成，空出一个空格，如果这行已经没有剩余空间，则另起一行
                if (--remain <= 0)
                {
                    remain = cols;
                    ++curRow;
                }
            }
            // 这一行剩余的空间不足以放下一条完整的句子，这条句子需要跨行显示
            else
            {
                int i = 0;  // 当前处理到第几个单词
                while (curRow < rows && i < n)
                {
                    // prefix[i][j] > remain, prefix[i][j-1] <= remain
                    int j = std::upper_bound(prefix[i].begin() + i, prefix[i].end(), remain) - prefix[i].begin();
                    // 剩余的空间连一个单词都放不下，换行
                    if (i == j)
                    {
                        ++curRow;
                        remain = cols;
                    }
                    // 这一行剩余的空间可以放下sentence[i:j-1]
                    else
                    {
                        remain -= prefix[i][j-1];
                        if (j == n) // 这条句子已经显示完成
                        {
                            ++ans;
                        }
                        // 输出完后要空出一个空格，如果这行已经没有剩余空间，则另起一行
                        if (--remain <= 0)
                        {
                            remain = cols;
                            ++curRow;
                        }
                        i = j;
                    }
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::string> sentence = {"I", "had", "apple", "pie"};
    int ans = solution.wordsTyping(sentence, 4, 5);
    std::cout << ans << std::endl;
    return 0;
}
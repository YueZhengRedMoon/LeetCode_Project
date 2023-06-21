#include <iostream>
#include <vector>
#include <algorithm>

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
            if (remain >= senLen)
            {
                ans += remain / senLen;
                remain = remain % senLen - 1;
            }
            else
            {
                int i = 0;
                while (curRow < rows && i < n && remain < prefix[i][n - 1])
                {
                    int index = std::lower_bound(prefix[i].begin(), prefix[i].end(), remain) - prefix[i].begin();
                    if (index == 0) // 这一行剩下的空间连一个单词也放不下
                    {
                        remain = cols;
                        ++curRow;

                        if (curRow < rows && remain >= prefix[i][n - 1])
                        {
                            remain -= prefix[i][n - 1] + 1;
                            ++ans;
                            break;
                        }
                    }
                    else
                    {
                        // prefix[i][i + index - 1] < remain
                        remain -= prefix[i][i + index - 1] + 1;
                        i += index;
                        if (i == n)
                        {
                            ++ans;
                            break;
                        }

                        if (remain >= prefix[i][n - 1])
                        {
                            remain -= prefix[i][n - 1] + 1;
                            ++ans;
                            break;
                        }
                    }
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
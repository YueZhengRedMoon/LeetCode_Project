#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::string> fullJustify(std::vector<std::string> &words, int maxWidth)
    {
        std::vector<std::string> ans;
        int curLen = 0; // 当前这一行的长度
        int curNum = 0; // 当前这一行单词的数目
        int start = 0;  // 这一行第一个单词的索引
        for (int i = 0; i < words.size(); ++i)
        {
            int newWordLen = words[i].size();
            // 当前行还能放入单词
            if (curLen + newWordLen + curNum <= maxWidth)
            {
                curLen += newWordLen;
                ++curNum;
            }
            // 当前行已经放不下单词
            else
            {
                // 输出当前行
                std::string line(maxWidth, ' ');
                // 当前行只有一个单词，不要考虑间隔
                if (curNum == 1)
                {
                    std::copy(words[start].begin(), words[start].end(), line.begin());
                }
                // 当前行有多个单词需要考虑间隔
                else
                {
                    int spaceNum = maxWidth - curLen;           // 剩余多少个空格
                    int space = spaceNum / (curNum - 1);        // 每个缝隙空格的数量
                    int residue = spaceNum % (curNum - 1);
                    auto begin = line.begin();
                    for (int j = start; j < i; ++j)
                    {
                        int len = words[j].size();
                        std::copy(words[j].begin(), words[j].end(), begin);
                        // 如果不能均匀隔开，前面的几个间隙要多加一个空格
                        if (j - start < residue)
                        {
                            begin += len + space + 1;
                        }
                        else
                        {
                            begin += len + space;
                        }
                    }
                }
                ans.push_back(line);

                // 开启新的一行
                start = i;
                curLen = newWordLen;
                curNum = 1;
            }
        }

        // 输出最后一行
        std::string line(maxWidth, ' ');
        auto begin = line.begin();
        for (int i = start; i < words.size(); ++i)
        {
            int len = words[i].size();
            std::copy(words[i].begin(), words[i].end(), begin);
            begin += len + 1;
        }
        ans.push_back(line);

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
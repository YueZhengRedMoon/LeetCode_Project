#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include "kirie_algorithm.h"
#include "debug/debug.h"

// kmp算法计算前缀表next数组
void getNext(std::vector<int> &next, const std::string &s)
{
    // i: 后缀的尾部
    // j+1: 前缀的尾部，同时也是最长相等前后缀的长度
    // next[i]: s[0:i]的最长相等前后缀的长度-1
    next[0] = -1;
    for (int i = 1, j = -1, len = s.size(); i < len; ++i)
    {
        while (j >= 0 && s[i] != s[j + 1])  // 前后缀尾部不相同
            j = next[j];                    // 回退j

        if (s[i] == s[j + 1])               // 前后缀尾部相同
            ++j;                            // 最长相等前后缀的长度+1

        next[i] = j;                        // 记录s[0:i]的最长相等前后缀的长度
    }
}

// 获取t在s中的出现次数
int kmpSearch(const std::string &s, const std::string &t)
{
    int sLen = s.size(), tLen = t.size(), cnt = 0;
    std::vector<int> next(tLen);
    getNext(next, t);
    int cmpCnt = 0;
    for (int i = 0, j = -1; i < sLen; ++i)
    {
        while (j >= 0)  // // 匹配失败
        {
            ++cmpCnt;
            if (s[i] != t[j + 1])
            {
                j = next[j];    // 回退到之前匹配的前缀的末尾
            }
            else
            {
                break;
            }
        }

        ++cmpCnt;
        if (s[i] == t[j + 1])               // 匹配成功
        {
            ++j;                            // 准备判断模式串的下一个字符
        }

        if (j == tLen - 1)                  // 找到一个匹配的字串
        {
            // 如果仅是判断t是否在s中出现，则此处直接return true;
            // 如果是要寻找t首次出现的索引，则返回 i + 1 - tLen

            std::cout << cmpCnt << std::endl;
            ++cnt;
            j = next[j];
        }
    }
    return cnt;
}

unsigned char fun(unsigned char data)
{
    data = (data << 4) | (data >> 4);
    data = ((data << 2) & 0xcc) | ((data >> 2) & 0x33);
    data = ((data << 1) & 0xaa) | ((data >> 1) & 0x55);
    return data;
}

int main()
{
    std::cout << (int) fun(209) << std::endl;
//    std::string s = "adabadabra", t = "adabr";
//    int cnt = kmpSearch(s, t);
//    std::cout << cnt << std::endl;
    return 0;
}

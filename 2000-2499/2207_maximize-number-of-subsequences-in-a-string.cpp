#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long maximumSubsequenceCount(std::string text, std::string pattern)
    {
        if (pattern[0] != pattern[1])
        {
            // pattern[0]和pattern[1]在text中出现的索引
            std::vector<int> indices0, indices1;
            for (int i = 0; i < text.size(); ++i)
            {
                if (text[i] == pattern[0])
                    indices0.push_back(i);
                else if (text[i] == pattern[1])
                    indices1.push_back(i);
            }

            // 计算在不插入的情况下，text中有多少个子序列与pattern相等
            long long ans = 0, cnt0 = indices0.size(), cnt1 = indices1.size();
            for (int i = 0, j = 0; i < cnt0 && j < cnt1; ++i)
            {
                while (j < cnt1 && indices1[j] < indices0[i])
                    ++j;
                ans += cnt1 - j;
            }

            return ans + std::max(cnt0, cnt1);
        }
        else
        {
            int cnt = std::count_if(text.begin(), text.end(), [pattern](char c) {return c == pattern[0];});
            return (cnt + 1ll) * cnt / 2ll;
        }
    }
};

class Solution2
{
public:
    long long maximumSubsequenceCount(std::string text, std::string pattern)
    {
        long long ans = 0;
        char x = pattern[0], y = pattern[1];
        int cntX = 0, cntY = 0;
        for (char c : text)
        {
            if (c == y)
            {
                ans += cntX;
                ++cntY;
            }
            if (c == x)
            {
                ++cntX;
            }
        }
        return ans + std::max(cntX, cntY);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

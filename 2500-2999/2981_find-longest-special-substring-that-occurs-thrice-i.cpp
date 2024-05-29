#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumLength(std::string s)
    {
        std::vector<std::pair<int, int>> ss[26];

        int n = s.size();
        for (int i = 0; i < n; ++i)
        {
            int c = s[i] - 'a';
            if (ss[c].empty())
                ss[c].emplace_back(i, i);
            else if (ss[c].back().second + 1 == i)
                ss[c].back().second = i;
            else
                ss[c].emplace_back(i, i);
        }

        auto len = [](const std::pair<int, int>& p) -> int {return p.second - p.first + 1;};

        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (ss[i].empty())
                continue;

            // 按特殊字符串的长度从小到大排序
            std::sort(ss[i].begin(), ss[i].end(),
                      [&len](const std::pair<int, int>& a, const std::pair<int, int>& b) {return len(a) < len(b);});

            if (len(ss[i].back()) > 2)
                ans = std::max(ans, len(ss[i].back()) - 2);

            // 二分查找找到第一个长度>ans的特殊字符串
            int left = 0, right = ss[i].size(), res = -1;
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (len(ss[i][mid]) > ans)
                {
                    res = mid;
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }

            if (res != -1)
            {
                n = ss[i].size();
                for (int j = res; j < n; ++j)
                {
                    int ssLen = len(ss[i][j]);
                    int tLen = std::min(ans + 1, ssLen);
                    while (tLen <= ssLen)
                    {
                        // 长度为l2的特殊字符串中包含l2-l1+1个长度为l1的特殊字符串(l1 <= l2)
                        int cnt = ssLen - tLen + 1, k = j + 1;
                        while (k < n && cnt < 3)
                        {
                            cnt += len(ss[i][k++]) - tLen + 1;
                        }
                        if (cnt >= 3)
                            ans = tLen;
                        ++tLen;
                    }
                }
            }
        }

        return ans ? ans : -1;
    }
};
int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

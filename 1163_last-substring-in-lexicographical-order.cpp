#include <iostream>
#include <vector>

class Solution
{
public:
    std::string lastSubstring(std::string s)
    {
        // i:当前找到的最大字典序的子串的起始索引
        // j:待比较的子串的起始索引
        int i = 0, j = 1, n = s.size();
        while (j < n)
        {
            int k = 0;
            // 跳过相同的前缀
            while (j + k < n && s[i + k] == s[j + k])
            {
                ++k;
            }
            // 在两个串第一处不一样的地方，如果待比较串字典序更大，则将待比较串记为当前最大字典序子串
            if (j + k < n && s[i + k] < s[j + k])
            {
                int t = i;
                i = j;  // 更新最大字典序子串的起始索引
                j = std::max(j + 1, t + k + 1); // 跳过已经比较过的部分
            }
            // s[i + k] > s[j + k]
            // 依然是当前串的字典序更大，待比较的串后移
            else
            {
                j = j + k + 1;
            }
        }
        return s.substr(i, n - i);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

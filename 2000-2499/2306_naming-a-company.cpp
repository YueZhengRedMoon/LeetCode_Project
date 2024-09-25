#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string_view>

class Solution
{
public:
    long long distinctNames(std::vector<std::string>& ideas)
    {
        // 按首字母分组
        std::unordered_set<std::string_view> groups[26];
        for (std::string_view s : ideas)
        {
            groups[s[0] - 'a'].insert(s.substr(1));
        }

        long long ans = 0;
        for (int a = 1; a < 26; ++a)    // 枚举所有组队
        {
            for (int b = 0; b < a; ++b)
            {
                int m = 0;  // groups[a]与groups[b]交集的大小
                for (std::string_view s : groups[a])
                {
                    m += groups[b].count(s);
                }
                ans += (long long) (groups[a].size() - m) * (groups[b].size() - m);
            }
        }
        return ans * 2;
    }
};

class Solution2
{
public:
    long long distinctNames(std::vector<std::string>& ideas)
    {
        int size[26]{}; // size[i]:以字母('a'+'i)为首字母的集合大小
        int intersection[26][26]{}; // intersection[a][b]:以a为首的字符串集合和以与b为首的字符串集合的交集的大小
        std::unordered_map<std::string_view, int> groups;   // 后缀 ->首字母
        for (std::string_view s : ideas)
        {
            int b = s[0] - 'a';
            ++size[b];
            std::string_view suffix = s.substr(1);  // 后缀
            int& mask = groups[suffix];
            mask |= (1 << b);
            for (int a = 0; a < 26; ++a)    // a是和s有相同后缀的字符串的首字母
            {
                if (mask & (1 << a))    // a在mask中
                {
                    ++intersection[b][a];
                    ++intersection[a][b];
                }
            }
        }

        long long ans = 0;
        for (int a = 1; a < 26; ++a)    // 枚举所有组队
        {
            for (int b = 0; b < a; ++b)
            {
                int m = intersection[a][b];
                ans += (long long) (size[a] - m) * (size[b] - m);
            }
        }
        return ans * 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

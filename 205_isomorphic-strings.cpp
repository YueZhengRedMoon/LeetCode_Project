#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    bool isIsomorphic(std::string s, std::string t)
    {
        std::unordered_map<char, char> s2t; // s到t的映射
        std::unordered_map<char, char> t2s; // t到s的映射
        for (int i = 0; i < s.size(); ++i)
        {
            // 不存在s[i]到t[i]的映射
            if (s2t.find(s[i]) == s2t.end())
            {
                // 已经有字符映射到t[i]了，不同字符不能映射到同一个字符上
                if (t2s.find(t[i]) != t2s.end())
                {
                    return false;
                }
                s2t[s[i]] = t[i];
                t2s[t[i]] = s[i];
            }
            // 存在从s[i]到t[i]的映射
            else
            {
                if (s2t[s[i]] != t[i])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

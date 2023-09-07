#include <iostream>
#include <vector>
#include <cstring>

class Solution
{
public:
    bool canBeEqual(std::string s1, std::string s2)
    {
        if (s1 == s2)
            return true;

        std::swap(s1[0], s1[2]);
        if (s1 == s2)
            return true;
        std::swap(s1[0], s1[2]);

        std::swap(s1[1], s1[3]);
        if (s1 == s2)
            return true;

        std::swap(s1[0], s1[2]);
        if (s1 == s2)
            return true;

        return false;
    }
};

class Solution2
{
public:
    bool canBeEqual(std::string s1, std::string s2)
    {
        int cnt1[2][26]{}, cnt2[2][26]{};
        for (int i = 0; i < s1.length(); ++i)
        {
            ++cnt1[i % 2][s1[i] - 'a'];
            ++cnt2[i % 2][s2[i] - 'a'];
        }
        return std::memcmp(cnt1, cnt2, sizeof(cnt1)) == 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

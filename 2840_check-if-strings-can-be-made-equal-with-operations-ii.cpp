#include <iostream>
#include <cstring>

class Solution
{
public:
    bool checkStrings(std::string s1, std::string s2)
    {
        int cnt1[2][26]{}, cnt2[2][26]{};
        int len = s1.size();
        for (int i = 0; i < len; ++i)
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

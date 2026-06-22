#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    int maxNumberOfBalloons(std::string text)
    {
        int cnt[26]{0};
        for (char c : text)
        {
            ++cnt[idx(c)];
        }
        return std::min({cnt[idx('b')], cnt[idx('a')], cnt[idx('l')] / 2, cnt[idx('o')] / 2, cnt[idx('n')]});
    }

private:
    int idx(char c)
    {
        return c - 'a';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
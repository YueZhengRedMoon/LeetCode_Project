#include <iostream>
#include <vector>

class Solution
{
public:
    int calculateTime(std::string keyboard, std::string word)
    {
        int index[26];
        for (int i = 0; i < 26; ++i)
        {
            index[ctoi(keyboard[i])] = i;
        }

        int cur = 0, ans = 0;
        for (char c : word)
        {
            int next = index[ctoi(c)];
            ans += std::abs(cur - next);
            cur = next;
        }

        return ans;
    }

private:
    int ctoi(char c)
    {
        return c - 'a';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
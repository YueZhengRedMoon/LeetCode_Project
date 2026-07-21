#include <iostream>
#include <vector>
#include <string>

class Solution
{
public:
    int maxActiveSectionsAfterTrade(std::string s)
    {
        int cnt1 = 0, mx = 0, pre0 = INT_MIN, cnt = 0, n = s.size();
        for (int i = 0; i < n; ++i)
        {
            ++cnt;
            if (i == n - 1 || s[i] != s[i + 1]) // i 是这一段的末尾
            {
                if (s[i] == '1')    // s[i + 1] == '0'
                {
                    cnt1 += cnt;
                }
                else
                {
                    mx = std::max(mx, pre0 + cnt);
                    pre0 = cnt;
                }
                cnt = 0;
            }
        }
        return cnt1 + mx;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
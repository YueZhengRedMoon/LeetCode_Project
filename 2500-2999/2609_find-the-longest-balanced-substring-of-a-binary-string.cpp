#include <iostream>
#include <vector>

class Solution
{
public:
    int findTheLongestBalancedSubstring(std::string s)
    {
        int n = s.size();
        int ans = 0, cnt0 = (s[0] == '0'), cnt1 = (s[0] == '1');
        for (int i = 1; i < n; ++i)
        {
            if (s[i - 1] == '1' && s[i] == '0')
            {
                ans = std::max(ans, 2 * std::min(cnt0, cnt1));
                cnt0 = 0;
                cnt1 = 0;
            }
            if (s[i] == '0')
                ++cnt0;
            else
                ++cnt1;
        }
        ans = std::max(ans, 2 * std::min(cnt0, cnt1));
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

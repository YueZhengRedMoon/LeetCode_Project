#include <iostream>
#include <vector>

class Solution
{
public:
    int longestContinuousSubstring(std::string s)
    {
        int ans = 1, cnt = 1;
        for (int i = 1; i < s.size(); ++i)
        {
            if (s[i - 1] + 1 == s[i])
            {
                ++cnt;
            }
            else
            {
                if (cnt > ans)
                {
                    ans = cnt;
                    if (ans == 26)
                        return ans;
                }
                cnt = 1;
            }
        }
        return std::max(ans, cnt);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

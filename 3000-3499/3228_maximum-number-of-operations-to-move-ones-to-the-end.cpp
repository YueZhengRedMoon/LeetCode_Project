#include <iostream>

class Solution
{
public:
    int maxOperations(std::string s)
    {
        int cnt1 = 0, ans = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '0')
            {
                // 跳过连续的0
                while ((i + 1) < s.size() && s[i + 1] == '0')
                    ++i;

                ans += cnt1;
            }
            else
            {
                ++cnt1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
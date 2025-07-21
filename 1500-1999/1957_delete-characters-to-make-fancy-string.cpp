#include <iostream>
#include <string>

class Solution
{
public:
    std::string makeFancyString(std::string s)
    {
        std::string ans;
        int n = s.size();
        ans.reserve(n);
        for (int i = 0, j = 0; i < n; ++i)
        {
            if (j < 2 || s[i] != ans[j - 1] || s[i] != ans[j - 2])
            {
                ans.push_back(s[i]);
                ++j;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

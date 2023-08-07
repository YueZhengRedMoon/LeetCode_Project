#include <iostream>
#include <algorithm>


class Solution
{
public:
    std::string finalString(std::string s)
    {
        std::string ans;
        ans.reserve(s.size());
        for (char c : s)
        {
            if (c == 'i')
            {
                std::reverse(ans.begin(), ans.end());
            }
            else
            {
                ans.push_back(c);
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

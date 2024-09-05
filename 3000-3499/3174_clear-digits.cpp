#include <iostream>
#include <vector>

class Solution
{
public:
    std::string clearDigits(std::string s)
    {
        std::string ans;
        ans.reserve(s.size());
        for (char c : s)
        {
            if (std::isdigit(c))
            {
                ans.pop_back();
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

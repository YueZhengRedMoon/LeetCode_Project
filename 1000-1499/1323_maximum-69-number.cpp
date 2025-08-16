#include <iostream>
#include <string>

class Solution
{
public:
    int maximum69Number (int num)
    {
        std::string s = std::to_string(num);
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '6')
            {
                s[i] = '9';
                break;
            }
        }
        return std::stoi(s);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

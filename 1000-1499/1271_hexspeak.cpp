#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    std::string toHexspeak(std::string num)
    {
        long long val = std::stoll(num);
        std::string ans;
        while (val > 0)
        {
            switch (val % 16)
            {
                case 15:
                    ans.push_back('F');
                    break;
                case 14:
                    ans.push_back('E');
                    break;
                case 13:
                    ans.push_back('D');
                    break;
                case 12:
                    ans.push_back('C');
                    break;
                case 11:
                    ans.push_back('B');
                    break;
                case 10:
                    ans.push_back('A');
                    break;
                case 1:
                    ans.push_back('I');
                    break;
                case 0:
                    ans.push_back('O');
                    break;
                default:
                    return "ERROR";
            }
            val /= 16;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

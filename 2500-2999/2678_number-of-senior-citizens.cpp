#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int countSeniors(std::vector<std::string> &details)
    {
        return std::count_if(details.begin(), details.end(),
                             [](const std::string &detail) -> bool
                             {
                                 return detail[11] > '6' || (detail[11] == '6' && detail[12] > '0');
                             });
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
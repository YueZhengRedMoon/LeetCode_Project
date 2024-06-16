#include <iostream>
#include <string>

class Solution
{
public:
    int findLUSlength(std::string a, std::string b)
    {
        return a == b ? -1 : std::max(a.size(), b.size());
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

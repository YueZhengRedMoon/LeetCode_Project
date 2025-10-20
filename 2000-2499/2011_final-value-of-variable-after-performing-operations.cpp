#include <iostream>
#include <vector>
#include <string_view>

class Solution
{
public:
    int finalValueAfterOperations(std::vector<std::string>& operations)
    {
        int ans = 0;
        for (std::string_view op : operations)
        {
            if (op[1] == '+')
                ++ans;
            else
                --ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
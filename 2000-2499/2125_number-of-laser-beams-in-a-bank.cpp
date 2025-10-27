#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>

class Solution
{
public:
    int numberOfBeams(std::vector<std::string>& bank)
    {
        int preCnt = 0, ans = 0;
        for (std::string_view s : bank)
        {
            int cnt = std::count_if(s.begin(), s.end(), [](char c) {return c == '1';});
            if (cnt > 0)
            {
                ans += preCnt * cnt;
                preCnt = cnt;
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
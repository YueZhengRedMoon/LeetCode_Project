#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findNumbers(std::vector<int>& nums)
    {
        return std::count_if(nums.begin(), nums.end(), [](int x) -> bool {
            int cnt = 0;
            while (x)
            {
                ++cnt;
                x /= 10;
            }
            return cnt % 2 == 0;
        });
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

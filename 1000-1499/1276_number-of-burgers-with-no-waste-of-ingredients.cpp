#include <iostream>
#include <vector>

class Solution
{
public:
    // t:tomatoSlices, c:cheeseSlices
    std::vector<int> numOfBurgers(int t, int c)
    {
        int x = (t - 2 * c) / 2, y = c - x;
        if (t < 2 * c || (t - 2 * c) % 2 || x < 0 || y < 0)
            return {};
        return {x, y};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

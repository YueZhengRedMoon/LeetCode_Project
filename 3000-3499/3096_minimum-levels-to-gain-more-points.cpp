#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumLevels(std::vector<int>& possible)
    {
        int n = possible.size();
        int aliceScore = 0;
        int bobScore = n - 2 * std::count_if(possible.begin(), possible.end(), [](int p) {return p == 0;});
        for (int i = 0; i < n - 1; ++i)
        {
            if (possible[i])
            {
                ++aliceScore;
                --bobScore;
            }
            else
            {
                --aliceScore;
                ++bobScore;
            }
            if (aliceScore > bobScore)
                return i + 1;
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

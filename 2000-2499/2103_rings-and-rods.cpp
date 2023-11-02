#include <iostream>
#include <vector>

class Solution
{
public:
    int countPoints(std::string rings)
    {
        int len  = rings.size();
        int n = len / 2;
        int rods[10][3]{0}; // [0]:R, [1]:G, [2]:B
        for (int i = 0; i < len; i += 2)
        {
            int color = 0;
            switch (rings[i])
            {
                case 'R':
                    color = 0;
                    break;
                case 'G':
                    color = 1;
                    break;
                case 'B':
                    color = 2;
                    break;
            }
            ++rods[rings[i + 1] - '0'][color];
        }
        int ans = 0;
        for (int i = 0; i < 10; ++i)
        {
            ans += (rods[i][0] && rods[i][1] && rods[i][2]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

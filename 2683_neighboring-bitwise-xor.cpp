#include <iostream>
#include <vector>

class Solution
{
public:
    bool doesValidArrayExist(std::vector<int> &derived)
    {
        int n = derived.size();
        int bits[2] = {0, 1};
        for (int i = 1; i <= n; ++i)
        {
            if (derived[i - 1] == 1)
            {
                bits[0] = 1 - bits[0];
                bits[1] = 1 - bits[1];
            }
        }
        return bits[0] == 0 && bits[1] == 1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

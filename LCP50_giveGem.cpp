#include <iostream>
#include <vector>

class Solution
{
public:
    int giveGem(std::vector<int> &gem, std::vector<std::vector<int>> &operations)
    {
        for (const std::vector<int> &op : operations)
        {
            int give = gem[op[0]] / 2;
            gem[op[0]] -= give;
            gem[op[1]] += give;
        }

        int minGem = gem[0], maxGem = gem[0];
        for (int g : gem)
        {
            if (g < minGem)
                minGem = g;
            if (g > maxGem)
                maxGem = g;
        }

        return maxGem - minGem;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumRefill(std::vector<int>& plants, int capacityA, int capacityB)
    {
        int ans = 0, n = plants.size();
        int i = 0, j = n - 1, sizeA = capacityA, sizeB = capacityB;
        while (i <= j)
        {
            if (i != j)
            {
                if (sizeA >= plants[i])
                {
                    sizeA -= plants[i];
                }
                else
                {
                    ++ans;
                    sizeA = capacityA - plants[i];
                }
                if (sizeB >= plants[j])
                {
                    sizeB -= plants[j];
                }
                else
                {
                    ++ans;
                    sizeB = capacityB - plants[j];
                }
            }
            else
            {
                ans += std::max(sizeA, sizeB) < plants[i];
            }
            ++i;
            --j;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

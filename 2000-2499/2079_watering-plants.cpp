#include <iostream>
#include <vector>

class Solution
{
public:
    int wateringPlants(std::vector<int>& plants, int capacity)
    {
        int ans = 0, n = plants.size(), remain = capacity;
        for (int i = 0; i < n; ++i)
        {
            if (remain >= plants[i])
            {
                remain -= plants[i];
                ++ans;
            }
            else
            {
                remain = capacity - plants[i];
                ans += 2 * i + 1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int minimumBoxes(std::vector<int>& apple, std::vector<int>& capacity)
    {
        int total = std::accumulate(apple.begin(), apple.end(), 0);
        std::sort(capacity.begin(), capacity.end(), std::greater<>());
        int ans = 0, capacitySum = 0;
        for (int i = 0; i < capacity.size() && capacitySum < total; ++i)
        {
            capacitySum += capacity[i];
            ++ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
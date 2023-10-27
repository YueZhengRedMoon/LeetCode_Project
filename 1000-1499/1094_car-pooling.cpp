#include <iostream>
#include <vector>
#include <cstring>

constexpr int MAX_TO = 1002;
int diff[MAX_TO];

class Solution
{
public:
    bool carPooling(std::vector<std::vector<int>> &trips, int capacity)
    {
        std::memset(diff, 0, sizeof(diff));
        for (const std::vector<int> &trip : trips)
        {
            int numPassengers = trip[0], from = trip[1], to = trip[2];
            diff[from] += numPassengers;
            diff[to] -= numPassengers;
        }

        int sum = 0;
        for (int d : diff)
        {
            sum += d;
            if (sum > capacity)
                return false;
        }

        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> trips = {{2, 1, 5}, {3, 5, 7}};
    int capacity = 3;
    bool ans = solution.carPooling(trips, capacity);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}

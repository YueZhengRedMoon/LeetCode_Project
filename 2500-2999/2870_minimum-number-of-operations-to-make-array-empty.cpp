#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minOperations(std::vector<int> &nums)
    {
        std::unordered_map<int, int> counter;
        for (int num : nums)
        {
            ++counter[num];
        }

        int ans = 0;
        for (auto [_, cnt] : counter)
        {
            if (cnt == 1)
                return -1;

            int x = cnt / 2, y = 0;    // cnt == 2 * x + 3 * y
            if (cnt % 2 == 1)
            {
                --x;
                ++y;
            }

            // 3个2可以凑成2个3
            y += (x / 3) * 2;
            x %= 3;

            ans += x + y;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

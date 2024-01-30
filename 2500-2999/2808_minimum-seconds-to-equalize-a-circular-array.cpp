#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minimumSeconds(std::vector<int> &nums)
    {
        int n = nums.size(), ans = n;
        std::unordered_map<int, std::vector<int>> pos;
        for (int i = 0; i < n; ++i)
        {
            pos[nums[i]].push_back(i);
        }

        for (auto &[num, idx] : pos)
        {
            int m = idx.size(), max = idx[0] + n - idx[m - 1];
            for (int i = 1; i < m; ++i)
            {
                max = std::max(max, idx[i] - idx[i - 1]);
            }
            ans = std::min(ans, max);
        }

        return ans / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

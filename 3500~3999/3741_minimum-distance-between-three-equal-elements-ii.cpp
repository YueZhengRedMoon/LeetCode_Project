#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minimumDistance(std::vector<int>& nums)
    {
        std::unordered_map<int, std::vector<int>> pos;
        int ans = INT_MAX;
        for (int k = 0; k < nums.size(); ++k)
        {
            int x = nums[k];
            std::vector<int>& posX = pos[x];
            posX.push_back(k);
            int m = posX.size();
            if (m >= 3)
            {
                int i = posX[m - 3], j = posX[m - 2];
                ans = std::min(ans, std::abs(i - j) + std::abs(j - k) + std::abs(k - i));
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
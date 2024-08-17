#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    std::vector<int> relocateMarbles(std::vector<int>& nums, std::vector<int>& moveFrom, std::vector<int>& moveTo)
    {
        std::unordered_set<int> marbles(nums.begin(), nums.end());

        int n = moveFrom.size();
        for (int i = 0; i < n; ++i)
        {
            int from = moveFrom[i], to = moveTo[i];
            if (from != to)
            {
                marbles.erase(from);
                marbles.insert(to);
            }
        }

        std::vector<int> ans(marbles.begin(), marbles.end());
        std::sort(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

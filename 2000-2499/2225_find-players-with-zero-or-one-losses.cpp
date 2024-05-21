#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> findWinners(std::vector<std::vector<int>>& matches)
    {
        std::unordered_map<int, int> lose;
        for (const auto& m : matches)
        {
            int winner = m[0], loser = m[1];
            ++lose[loser];
            if (lose.find(winner) == lose.end())
                lose[winner] = 0;
        }

        std::vector<std::vector<int>> ans(2, std::vector<int>());
        for (auto [loser, cnt] : lose)
        {
            if (cnt <= 1)
                ans[cnt].push_back(loser);
        }

        std::sort(ans[0].begin(), ans[0].end());
        std::sort(ans[1].begin(), ans[1].end());

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

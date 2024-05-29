#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumLength(std::string s)
    {
        std::vector<std::vector<int>> groups(26, std::vector<int>(2, 0));
        int cnt = 0, n = s.size();
        for (int i = 0; i < n; ++i)
        {
            ++cnt;
            if (i + 1 == n || s[i] != s[i + 1])
            {
                groups[s[i] - 'a'].push_back(cnt);
                cnt = 0;
            }
        }

        int ans = 0;
        for (auto& g : groups)
        {
            if (g.size() < 3)
                continue;

            std::nth_element(g.begin(), g.begin() + 2, g.end(), std::greater<>());
            if (g[0] < g[1])
                std::swap(g[0], g[1]);

            ans = std::max({ans, g[0] - 2, std::min(g[0] - 1, g[1]), g[2]});
        }

        return ans ? ans : -1;
    }
};

int main()
{
    Solution solution;
    std::string s = "ceeeeeeeeeeeebmmmfffeeeeeeeeeeeewww";
    int ans = solution.maximumLength(s);
    std::cout << ans << std::endl;
    return 0;
}

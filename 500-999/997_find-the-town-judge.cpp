#include <iostream>
#include <vector>

class Solution
{
public:
    int findJudge(int n, std::vector<std::vector<int>>& trust)
    {
        // first:入度 second:出度
        std::vector<std::pair<int, int>> degrees(n + 1);
        for (const std::vector<int>& t : trust)
        {
            int a = t[0], b = t[1];
            ++degrees[a].second;
            ++degrees[b].first;
        }

        int ans = -1;
        for (int i = 1; i <= n; ++i)
        {
            if (degrees[i].first == n - 1 && degrees[i].second == 0)
            {
                if (ans == -1)
                    ans = i;
                else
                    return -1;
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

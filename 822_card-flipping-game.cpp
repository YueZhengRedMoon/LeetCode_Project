#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution
{
public:
    int flipgame(std::vector<int> &fronts, std::vector<int> &backs)
    {
        int n = fronts.size();
        std::vector<std::pair<int, int>> cards(n);
        std::unordered_set<int> frontsSet;
        for (int i = 0; i < n; ++i)
        {
            cards[i].first = fronts[i];
            cards[i].second = backs[i];
            frontsSet.emplace(fronts[i]);
        }
        std::sort(cards.begin(), cards.end());

        const int inf = 0x3f3f3f3f;
        int i = 0, j, ans = inf;
        auto checkBack = [&](int back) -> void {
            if (frontsSet.find(back) == frontsSet.end() && back < ans)
                ans = back;
        };
        while (i < n)
        {
            checkBack(cards[i].second);

            if (cards[i].first == cards[i].second)
            {
                j = i + 1;
                while (j < n && cards[j].first == cards[i].first)
                {
                    checkBack(cards[j].second);
                    ++j;
                }
                i = j;
                continue;
            }

            j = i + 1;
            bool isGood = true;
            while (j < n && cards[i].first == cards[j].first)
            {
                checkBack(cards[j].second);
                if (cards[j].second == cards[i].first)
                    isGood = false;
                ++j;
            }
            if (isGood && cards[i].first < ans)
                ans = cards[i].first;
            i = j;
        }

        return ans == inf ? 0 : ans;
    }
};

class Solution2
{
public:
    int flipgame(std::vector<int> &fronts, std::vector<int> &backs)
    {
        int ans = 3000, n = fronts.size();
        std::unordered_set<int> same;
        for (int i = 0; i < n; ++i)
        {
            if (fronts[i] == backs[i])
            {
                same.insert(fronts[i]);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            if (fronts[i] < ans && same.find(fronts[i]) == same.end())
                ans = fronts[i];

            if (backs[i] < ans && same.find(backs[i]) == same.end())
                ans = backs[i];
        }

        return ans % 3000;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
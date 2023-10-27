#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int miceAndCheese(std::vector<int> &reward1, std::vector<int> &reward2, int k)
    {
        int n = reward1.size();
        std::vector<std::pair<int, int>> reward(n);
        for (int i = 0; i < n; ++i)
        {
            reward[i].first = reward1[i];
            reward[i].second = reward2[i];
        }
        std::sort(reward.begin(), reward.end(),
                  [](const std::pair<int, int> &lhs, const std::pair<int, int> &rhs)
                  {
                        int delta1 = lhs.first - lhs.second;
                        int delta2 = rhs.first - rhs.second;
                        if (delta1 == delta2)
                        {
                            return lhs.first > rhs.first;
                        }
                        return delta1 > delta2;
                  });
        int ans = 0;
        for (int i = 0; i < k; ++i)
        {
            ans += reward[i].first;
        }
        for (int i = k; i < n; ++i)
        {
            ans += reward[i].second;
        }
        return ans;
    }
};

class Solution2
{
public:
    int miceAndCheese(std::vector<int> &reward1, std::vector<int> &reward2, int k)
    {
        for (int i = 0; i < reward1.size(); ++i)
        {
            reward1[i] -= reward2[i];
        }
        std::nth_element(reward1.begin(), reward1.end() - k, reward1.end());
        return  std::accumulate(reward1.end() - k, reward1.end(), 0) +
                std::accumulate(reward2.begin(), reward2.end(), 0);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
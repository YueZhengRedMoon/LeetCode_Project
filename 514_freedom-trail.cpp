#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int findRotateSteps(std::string ring, std::string key)
    {
        int ringSize = ring.size();
        // 每个字母出现的索引
        std::vector<int> indices[26];
        for (int i = 0; i < ringSize; ++i)
        {
            indices[ring[i] - 'a'].push_back(i);
        }

        // dp[i][j]:输入key[i-1]后，输入ring[j]需要的最少步数
        std::vector<std::vector<int>> dp(2, std::vector<int>(ringSize, 0));
        for (int index : indices[key[0] - 'a'])
        {
            dp[0][index] = std::min(index, ringSize - index) + 1;
        }

        for (int i = 1; i < key.size(); ++i)
        {
            int lastAlpha = key[i - 1] - 'a';    // 上一个输入的字母的序号
            int currentAlpha = key[i] - 'a';     // 当前要输入的字母的序号
            int last = (i - 1) % 2;
            int current = i % 2;
            // 遍历当前字母的每个位置
            for (int currentIndex : indices[currentAlpha])
            {
                dp[current][currentIndex] = std::numeric_limits<int>::max();
                for (int lastIndex : indices[lastAlpha])
                {
                    dp[current][currentIndex] = std::min(dp[current][currentIndex],
                                                         dp[last][lastIndex] +
                                                         std::min(std::abs(lastIndex - currentIndex), ringSize - std::abs(lastIndex - currentIndex)) + 1);
                }
            }
        }

        int result = std::numeric_limits<int>::max();
        int end = (key.size() - 1) % 2;
        for (int index : indices[key.back() - 'a'])
        {
            result = std::min(result, dp[end][index]);
        }

        return result;
    }
};

int main()
{
    Solution solution;
    std::string ring = "godding", key = "godding";
    int reuslt = solution.findRotateSteps(ring, key);
    std::cout << reuslt << std::endl;
    return 0;
}
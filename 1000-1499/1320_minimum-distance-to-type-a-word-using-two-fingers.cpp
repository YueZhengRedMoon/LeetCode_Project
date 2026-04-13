#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

int dis[26][26];
// 预处理两个字母的距离
auto init = [] () {
    constexpr int COLUMN = 6;
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            dis[i][j] = std::abs(i / COLUMN - j / COLUMN) + std::abs(i % COLUMN - j % COLUMN);
        }
    }
    return 0;
}();

class Solution
{
public:
    int minimumDistance(std::string word)
    {
        int n = word.size();
        std::vector<std::vector<std::vector<int>>> memo(n, std::vector<std::vector<int>>(26, std::vector<int>(26, -1)));    // -1 表示没有计算过
        std::function<int(int, int, int)> dfs = [&](int i, int finger1, int finger2) -> int {
            if (i < 0)
            {
                return 0;
            }

            int& res = memo[i][finger1][finger2];
            if (res != -1)  // 之前计算过
            {
                return res;
            }

            // 手指 1 移到 word[i]
            int w = word[i] - 'A';
            int res1 = dfs(i - 1, w, finger2) + dis[finger1][w];

            // 手指 2 移到 word[i]
            int res2 = dfs(i - 1, finger1, w) + dis[finger2][w];

            res = std::min(res1, res2);
            return res;
        };

        int ans = INT_MAX;
        // 最后一定有一根手指在 word[n-1]，另一根手指的位置不确定，枚举
        for (int finger2 = 0; finger2 < 26; ++finger2)
        {
            ans = std::min(ans, dfs(n - 2, word[n - 1] - 'A', finger2));
        }
        return ans;
    }
};

namespace WrongSolution
{
    std::pair<int, int> pos[26];
    int init = [](){
        int k = 0;
        for (int i = 0; i < 5 && k < 26; ++i)
        {
            for (int j = 0; j < 6 && k < 26; ++j)
            {
                pos[k++] = {i, j};
            }
        }
        return 0;
    }();

    class Solution
    {
    public:
        int minimumDistance(std::string word)
        {
            int ans = INT_MAX, n = word.size();
            std::unordered_map<int, int> memo;
            std::function<void(int, char, char, int)> dfs = [&](int i, char f1, char f2, int dis)
            {
                int key = getKey(i, f1, f2);
                auto it = memo.find(key);
                if (it != memo.end() && it->second <= dis)
                {
                    return;
                }

                memo[key] = dis;
                if (i == n)
                {
                    ans = std::min(ans, dis);
                    return;
                }

                char next = word[i];
                dfs(i + 1, next, f2, dis + getDis(f1, next));
                dfs(i + 1, f1, next, dis + getDis(f2, next));
            };
            dfs(0, 0, 0, 0);
            return ans;
        }

    private:
        int getKey(int i, int f1, int f2)
        {
            return (i << 10) | (f1 << 5) | f2;
        }

        int getDis(char from, char to)
        {
            if (from == 0)
            {
                return 0;
            }
            int i = from - 'A', j = to - 'A';
            return std::abs(pos[i].first - pos[j].first) + std::abs(pos[i].second - pos[j].second);
        }
    };
}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
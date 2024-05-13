#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

class Solution
{
public:
    int minimumRounds(std::vector<int>& tasks)
    {
        std::unordered_map<int, int> counter;
        for (int t : tasks)
        {
            ++counter[t];
        }

        int ans = 0;
        for (auto it = counter.begin(); it != counter.end(); ++it)
        {
            int cnt = it->second;
            int op = INT_MAX;
            for (int x = 0; x <= cnt; x += 3)
            {
                int y = cnt - x;
                if (y % 2 == 0)
                    op = std::min(op, x / 3 + y / 2);
            }
            if (op == INT_MAX)
                return -1;
            ans += op;
        }

        return ans;
    }
};

class Solution2
{
public:
    int minimumRounds(std::vector<int>& tasks)
    {
        std::unordered_map<int, int> counter;
        for (int t : tasks)
        {
            ++counter[t];
        }

        int ans = 0;
        for (auto it = counter.begin(); it != counter.end(); ++it)
        {
            int cnt = it->second;
            if (cnt == 1)
                return -1;
            ans += (cnt + 2) / 3;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

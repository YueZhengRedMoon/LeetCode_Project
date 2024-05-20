#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int longestAwesome(std::string s)
    {
        int n = s.size();
        std::vector<int> f(n);
        f[0] = getState(s[0]);
        for (int i = 1; i < n; ++i)
        {
            f[i] = f[i - 1] ^ getState(s[i]);
        }

        std::unordered_map<int, int> stateMap;
        for (int i = 0; i < n; ++i)
        {
            stateMap[f[i]] = i;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int state = f[i];
            if (state == 0 || (state & (state - 1)) == 0)
            {
                ans = std::max(ans, i + 1);
            }
            ans = std::max(ans, longestAwesome(f[i], i, stateMap));
        }

        return ans;
    }

private:
    int getState(char c)
    {
        return 1 << (c - '0');
    }

    int longestAwesome(int state, int idx, std::unordered_map<int, int>& stateMap)
    {
        int res = std::max(stateMap[state] - idx, 1);
        for (int i = 0; i <= 9; ++i)
        {
            int newState;
            if (state & (1 << i))   // state第i位为1
            {
                newState = state & ~(1 << i);
            }
            else    // state第i位为0
            {
                newState = state | (1 << i);
            }
            auto it = stateMap.find(newState);
            if (it != stateMap.end())
                res = std::max(res, it->second - idx);
        }
        return res;
    }
};

int main()
{
    Solution solution;
    std::string s = "3242415";
    int ans = solution.longestAwesome(s);
    std::cout << ans << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

class Solution
{
public:
    int maxScoreSightseeingPair(std::vector<int>& v)
    {
        // vi + vj + i - j变形为(vi+i)+(vj-j)
        // 枚举j，同时维护j左边的vi+i的最大值mx，然后用mx+vj-j更新答案的最大值
        int ans = 0, mx = v[0];    // mx表示j左边的v[i]+i的最大值
        for (int j = 1; j < v.size(); ++j)
        {
            ans = std::max(ans, mx + v[j] - j);
            mx = std::max(mx, v[j] + j);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

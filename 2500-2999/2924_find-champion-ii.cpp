#include <iostream>
#include <vector>

class Solution
{
public:
    int findChampion(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<int> inDeg(n);
        for (const auto& e : edges)
        {
            ++inDeg[e[1]];
        }
        int ans = -1;
        for (int x = 0; x < n; ++x)
        {
            if (inDeg[x] == 0)
            {
                if (ans != -1)
                    return -1;
                ans = x;
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

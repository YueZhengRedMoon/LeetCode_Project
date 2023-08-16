#include <iostream>
#include <vector>
#include <bitset>

class Solution
{
public:
    std::vector<int> circularGameLosers(int n, int k)
    {
        std::bitset<50> visited;
        int cur = 0, i = 1;
        while (!visited[cur])
        {
            visited[cur] = true;
            cur = (cur + i * k) % n;
            ++i;
        }
        std::vector<int> ans;
        for (i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                ans.push_back(i + 1);
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

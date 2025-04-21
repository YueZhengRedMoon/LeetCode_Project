#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int numRabbits(std::vector<int>& answers)
    {
        std::unordered_map<int, int> counter;
        for (int x : answers)
        {
            ++counter[x];
        }

        int ans = 0;
        for (auto it = counter.begin(); it != counter.end(); ++it)
        {
            int x = it->first, cnt = it->second;
            ans += ((cnt + x) / (x + 1)) * (x + 1); // ceil(cnt/(x+1) * (x + 1)
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

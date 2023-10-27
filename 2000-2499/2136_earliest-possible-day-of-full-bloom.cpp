#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    int earliestFullBloom(std::vector<int> &plantTime, std::vector<int> &growTime)
    {
        int n = plantTime.size();
        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(), [&](int lhs, int rhs) {
            return growTime[lhs] > growTime[rhs];
        });

        int ans = 0, plantTimeSum = 0;
        for (int i : id)
        {
            plantTimeSum += plantTime[i];
            ans = std::max(ans, plantTimeSum + growTime[i]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

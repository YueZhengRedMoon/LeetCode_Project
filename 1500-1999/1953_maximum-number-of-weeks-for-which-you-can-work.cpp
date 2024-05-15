#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long numberOfWeeks(std::vector<int>& milestones)
    {
        int n = milestones.size();
        auto maxIt = std::max_element(milestones.begin(), milestones.end());
        std::iter_swap(maxIt, milestones.begin());
        long long sum = milestones[0], remain = milestones[0] - 1;
        for (int i = 1; i < n; ++i)
        {
            sum += milestones[i];
            remain -= milestones[i];
        }
        return sum - std::max(remain, 0ll);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

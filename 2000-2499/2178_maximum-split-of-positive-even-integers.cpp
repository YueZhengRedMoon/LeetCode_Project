#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<long long> maximumEvenSplit(long long finalSum)
    {
        if (finalSum % 2 == 1)
            return {};

        std::vector<long long> ans;
        for (long long i = 2; i <= finalSum; i += 2)
        {
            ans.push_back(i);
            finalSum -= i;
        }
        ans.back() += finalSum;
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
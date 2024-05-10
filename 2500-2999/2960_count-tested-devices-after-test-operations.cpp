#include <iostream>
#include <vector>

class Solution
{
public:
    int countTestedDevices(std::vector<int>& batteryPercentages)
    {
        int tested = 0;
        for (int p : batteryPercentages)
        {
            tested += p > tested;
        }
        return tested;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

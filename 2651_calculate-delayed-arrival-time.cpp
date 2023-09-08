#include <iostream>
#include <vector>

class Solution
{
public:
    int findDelayedArrivalTime(int arrivalTime, int delayedTime)
    {
        return (arrivalTime + delayedTime) % 24;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

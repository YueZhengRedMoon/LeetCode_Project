#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int numberOfEmployeesWhoMetTarget(std::vector<int>& hours, int target)
    {
        return std::count_if(hours.begin(), hours.end(), [target](int hour) -> bool {return hour >= target;});
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

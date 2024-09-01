#include <iostream>
#include <vector>

class Solution
{
public:
    int busyStudent(std::vector<int>& startTime, std::vector<int>& endTime, int queryTime)
    {
        int n = startTime.size(), ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += startTime[i] <= queryTime && queryTime <= endTime[i];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

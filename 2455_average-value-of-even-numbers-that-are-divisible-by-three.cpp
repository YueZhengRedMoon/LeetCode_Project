#include <iostream>
#include <vector>

class Solution
{
public:
    int averageValue(std::vector<int> &nums)
    {
        int sum = 0, count = 0;
        for (int num : nums)
        {
            if (num % 6 == 0)
            {
                sum += num;
                ++count;
            }
        }
        return count > 0 ? sum / count : 0;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
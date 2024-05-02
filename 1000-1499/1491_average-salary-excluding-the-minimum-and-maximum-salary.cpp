#include <iostream>
#include <vector>

class Solution
{
public:
    double average(std::vector<int>& salary)
    {
        int n = salary.size();
        int sum = 0, max = salary[0], min = salary[0];
        for (int s : salary)
        {
            sum += s;
            if (s > max)
            {
                max = s;
            }
            else if (s < min)
            {
                min = s;
            }
        }
        return (double) (sum - max - min) / (n - 2);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

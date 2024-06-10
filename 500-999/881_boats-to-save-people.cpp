#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int numRescueBoats(std::vector<int>& people, int limit)
    {
        std::sort(people.begin(), people.end());
        int ans = 0, n = people.size();
        int i = 0, j = n - 1;
        while (i <= j)
        {
            ++ans;
            if (i == j)
                break;

            if (people[i] + people[j] <= limit)
            {
                ++i;
            }
            --j;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

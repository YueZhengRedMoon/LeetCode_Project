#include <iostream>
#include <vector>

class Solution
{
public:
    int distanceBetweenBusStops(std::vector<int>& distance, int start, int destination)
    {
        int sum = 0, disToDes = 0, i = start, n = distance.size();
        do
        {
            if (i == destination)
            {
                disToDes = sum;
            }
            sum += distance[i];
            i = (i + 1) % n;
        } while (i != start);
        return std::min(disToDes, sum - disToDes);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

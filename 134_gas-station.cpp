#include <iostream>
#include <vector>

void printVector(const std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

class Solution
{
public:
    int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost)
    {
        int sum = 0;
        int min = 0;
        int minIndex = 0;
        for (int i = 0; i < gas.size(); ++i)
        {
            gas[i] -= cost[i];
            sum += gas[i];

            if (gas[i] <= min)
            {
                min = gas[i];
                minIndex = i;
            }
        }

        std::cout << "gas - cost:" << std::endl;
        printVector(gas);

        std::cout << "sum = " << sum << std::endl;
        std::cout << "min = " << min << ", minIndex = " << minIndex << std::endl;

        if (sum >= 0)
        {
            int need = min;
            int i = minIndex;
            if (minIndex == gas.size() - 1 && gas[i] < 0)
            {
                i = 0;
                while (gas[i] <= min)
                {
                    ++i;
                }
                i = i > 0 ? i - 1 : gas.size() - 1;
            }
            while (need < 0)
            {
                i = i > 0 ? i - 1 : gas.size() - 1;
                need += gas[i];
            }
            return i;
        }
        else
        {
            return -1;
        }
    }
};

int main()
{
    // 4 5 8 2 8 6 5 6 6
    std::vector<int> gas = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    std::vector<int> cost = {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
//    int n;
//    std::cin >> n;
//    for (int i = 0; i < n; ++i)
//    {
//        int value;
//        std::cin >> value;
//        gas.push_back(value);
//    }
//    for (int i = 0; i < n; ++i)
//    {
//        int value;
//        std::cin >> value;
//        cost.push_back(value);
//    }
    Solution solution;
    std::cout << solution.canCompleteCircuit(gas, cost) << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost)
    {
        for (unsigned int i = 0; i <cost.size(); ++i)
        {
            int rest = gas[i] - cost[i];    // 记录剩余油量
            unsigned int index = (i + 1) % cost.size();
            while (rest > 0 && index != i)
            {
                rest += gas[index] - cost[i];
                index = (index + 1) % cost.size();
            }
            // 如果以i为起点跑一圈，剩余油量>=0，返回该起始位置
            if (rest >= 0 && index == i)
            {
                return i;
            }
        }
        return -1;
    }
};

class Solution2
{
public:
    int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost)
    {
        int currentSum = 0;
        int min = std::numeric_limits<int>::max();  // 从起点出发，油箱里的油量最小值
        for (unsigned int i = 0; i < gas.size(); ++i)
        {
            int rest = gas[i] - cost[i];
            currentSum += rest;
            if (currentSum < min)
            {
                min = currentSum;
            }
        }

        if (currentSum < 0) return -1;
        if (min >= 0) return 0;
        for (int i = gas.size() - 1; i >= 0; --i)
        {
            int rest = gas[i] - cost[i];
            min += rest;
            if (min >= 0)
            {
                return i;
            }
        }
        return -1;
    }
};

class Solution3
{
public:
    int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost)
    {
        int currentSum = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); ++i)
        {
            int rest = gas[i] - cost[i];
            currentSum += rest;
            totalSum += rest;
            if (currentSum < 0)
            {
                start = i + 1;
                currentSum = 0;
            }
        }
        if (totalSum < 0) return -1;
        else return start;
    }
};

int main()
{
    // 4 5 8 2 8 6 5 6 6
    std::vector<int> gas1 = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    std::vector<int> cost1 = {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    std::vector<int> gas2 = {3,3,3,3,3,3,3,3};
    std::vector<int> cost2 = {5,1,4,4,4,2,2,2};
    std::vector<int> gas3 = {6, 1, 4, 3, 5};
    std::vector<int> cost3 = {3, 8, 2, 4, 2};
    Solution3 solution;
    std::cout << solution.canCompleteCircuit(gas1, cost1) << std::endl;
    std::cout << solution.canCompleteCircuit(gas2, cost2) << std::endl;
    std::cout << solution.canCompleteCircuit(gas3, cost3) << std::endl;
    return 0;
}
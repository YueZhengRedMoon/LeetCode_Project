#include <iostream>
#include <vector>

class Solution
{
public:
    int hardestWorker(int n, std::vector<std::vector<int>> &logs)
    {
        int maxTime = logs[0][1];
        int id = logs[0][0];
        for (int i = 1; i < logs.size(); ++i)
        {
            int time = logs[i][1] - logs[i - 1][1];
            if (time > maxTime)
            {
                maxTime = time;
                id = logs[i][0];
            }
            else if (time == maxTime && id > logs[i][0])
            {
                id = logs[i][0];
            }
        }
        return id;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
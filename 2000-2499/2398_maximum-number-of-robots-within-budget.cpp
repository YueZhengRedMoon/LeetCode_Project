#include <iostream>
#include <vector>
#include <deque>

class Solution
{
public:
    int maximumRobots(std::vector<int>& chargeTimes, std::vector<int>& runningCosts, long long budget)
    {
        int n = chargeTimes.size(), left = 0, ans = 0;
        long long sum = 0;
        std::deque<int> deque;  // 单调递减队列，队首元素是最大chargeTime的索引
        for (int right = 0; right < chargeTimes.size(); ++right)
        {
            // 1.入
            while (!deque.empty() && chargeTimes[right] >= chargeTimes[deque.back()])
            {
                deque.pop_back();
            }
            deque.push_back(right);
            sum += runningCosts[right];

            // 2.出
            while (!deque.empty() && chargeTimes[deque.front()] + (right - left + 1) * sum > budget)
            {
                if (left == deque.front())
                    deque.pop_front();
                sum -= runningCosts[left++];
            }

            // 3.更新答案
            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

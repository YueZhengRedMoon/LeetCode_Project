#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int halveArray(std::vector<int> &nums)
    {
        std::priority_queue<double, std::vector<double>, std::less<>> maxHeap;
        double sum = 0.0;
        for (int num : nums)
        {
            sum += num;
            maxHeap.emplace(num);
        }

        int ans = 0;
        double reduce = 0.0, target = sum / 2.0;
        while (reduce < target)
        {
            double max = maxHeap.top();
            maxHeap.pop();
            max /= 2.0;
            reduce += max;
            maxHeap.emplace(max);
            ++ans;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
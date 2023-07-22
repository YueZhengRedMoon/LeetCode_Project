#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int connectSticks(std::vector<int> &sticks)
    {
        int ans = 0;
        std::priority_queue<int, std::vector<int>, std::greater<>> minHeap;
        for (int len : sticks)
        {
            minHeap.emplace(len);
        }

        while (minHeap.size() >= 2)
        {
            int len1 = minHeap.top();
            minHeap.pop();
            int len2 = minHeap.top();
            minHeap.pop();
            int newLen = len1 + len2;
            ans += newLen;
            minHeap.emplace(newLen);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Solution
{
public:
    int minOperations(std::vector<int>& numsInt, int k)
    {
        std::vector<long long> nums(numsInt.begin(), numsInt.end());

        std::make_heap(nums.begin(), nums.end(), std::greater<>()); // 构造小顶堆
        int heapSize = nums.size();
        int ans = 0;
        while (heapSize >= 2 && nums[0] < k)
        {
            long long x = nums[0];
            std::pop_heap(nums.begin(), nums.begin() + heapSize, std::greater<>());
            long long y = nums[0];
            std::pop_heap(nums.begin(), nums.begin() + heapSize - 1, std::greater<>());

            nums[heapSize - 2] = std::min(x, y) * 2LL + std::max(x, y);
            std::push_heap(nums.begin(), nums.begin() + heapSize - 1, std::greater<>());

            --heapSize;
            ++ans;
        }
        return ans;
    }
};

class Solution2
{
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        std::priority_queue<long long, std::vector<long long>, std::greater<>> minHeap(nums.begin(), nums.end());
        int ans = 0;
        while (minHeap.top() < k)
        {
            long long x = minHeap.top();
            minHeap.pop();
            long long y = minHeap.top();
            minHeap.pop();

            minHeap.push(std::min(x, y) * 2LL + std::max(x, y));
            ++ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

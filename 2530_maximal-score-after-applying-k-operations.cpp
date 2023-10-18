#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    long long maxKelements(std::vector<int> &nums, int k)
    {
        long long ans = 0;
        std::priority_queue<int, std::vector<int>, std::less<>> maxHeap(nums.begin(), nums.end());
        for (int i = 0; i < k; ++i)
        {
            int maxNum = maxHeap.top();
            maxHeap.pop();
            ans += maxNum;
            maxHeap.push((maxNum + 2) / 3); // maxNum / 3相互三个取整
        }
        return ans;
    }
};

class Solution2
{
public:
    long long maxKelements(std::vector<int> &nums, int k)
    {
        std::make_heap(nums.begin(), nums.end(), std::less<>());   // 原地堆化（最大堆）
        long long ans = 0;
        while (k--)
        {
            std::pop_heap(nums.begin(), nums.end());    // 把堆顶移到末尾
            ans += nums.back();
            nums.back() = (nums.back() + 2) / 3;
            std::push_heap(nums.begin(), nums.end());   // 把末尾元素入堆
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

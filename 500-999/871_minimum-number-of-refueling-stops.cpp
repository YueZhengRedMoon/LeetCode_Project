#include <iostream>
#include <vector>
#include "../debug/debug.h"

class MaxHeap
{
public:
    MaxHeap(size_t capacity) : heap(capacity), size(0) {}

    void push(int val)
    {
        int i = size++;
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] < val)
            {
                heap[i] = heap[parent];
                i = parent;
            }
            else
            {
                break;
            }
        }
        heap[i] = val;
    }

    int pop()
    {
        int ret = heap[0], x = heap[--size], i = 0;
        while (i * 2 + 1 < size)
        {
            int left = i * 2 + 1, right = i * 2 + 2;
            int max = left;
            if (right < size && heap[right] > heap[left])
            {
                max = right;
            }
            if (x < heap[max])
            {
                heap[i] = heap[max];
                i = max;
            }
            else
            {
                break;
            }
        }
        heap[i] = x;
        return ret;
    }

    bool empty() const
    {
        return size == 0;
    }

private:
    std::vector<int> heap;
    size_t size;
};

class Solution
{
public:
    int minRefuelStops(int target, int startFuel, std::vector<std::vector<int>> &stations)
    {
        stations.push_back({target, 0});
        int ans = 0, curPos = 0, curFuel = startFuel, n = stations.size();
        MaxHeap maxHeap(n);
        for (const std::vector<int> &station : stations)
        {
            int position = station[0], fuel = station[1];

            curFuel -= position - curPos;
            while (curFuel < 0 && !maxHeap.empty()) // 燃料不足，反悔，从经过的加油站中选择燃料最多的加油站加油
            {
                ++ans;  // 加一次油
                curFuel += maxHeap.pop();
            }
            if (curFuel < 0)    // 经过的每个加油站都加油任然无法到达下一个加油站
            {
                return -1;
            }

            maxHeap.push(fuel); // 贪心，到达加油站后不加油
            curPos = position;  // 更新当前位置
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> stations = {{25, 25},{50, 50}};
    int target = 100, startFuel = 50;
    int ans = solution.minRefuelStops(target, startFuel, stations);
    logObj(ans);
    return 0;
}

#include <iostream>
#include <vector>

class MinHeap
{
public:
    MinHeap(int capacity) : size(0), heap(capacity) {}

    void push(int val)
    {
        int i = size++;
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (heap[p] < val)
                break;
            heap[i] = heap[p];
            i = p;
        }
        heap[i] = val;
    }

    int pop()
    {
        int ret = heap[0], x = heap[--size], i = 0;
        while (i * 2 + 1 < size)
        {
            int left = i * 2 + 1, right = i * 2 + 2, min = left;
            if (right < size && heap[right] < heap[left])
                min = right;
            if (x < heap[min])
                break;
            heap[i] = heap[min];
            i = min;
        }
        heap[i] = x;
        return ret;
    }

    bool empty() const
    {
        return size == 0;
    }

private:
    size_t size;
    std::vector<int> heap;
};

class Solution
{
public:
    int magicTower(std::vector<int> &nums)
    {
        int n = nums.size(), ans = 0;
        long long hp = 1, sum = 0;
        MinHeap minHeap(n);
        for (int i = 0; i < n; ++i)
        {
            hp += nums[i];
            if (nums[i] < 0)
            {
                minHeap.push(nums[i]);
            }

            while (hp <= 0 && !minHeap.empty())
            {
                int top = minHeap.pop();    // top < 0
                hp -= top;
                sum += top;
                ++ans;
            }
        }

        hp += sum;
        return hp > 0 ? ans : -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

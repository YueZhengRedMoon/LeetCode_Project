#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

class Solution
{
public:
    long long pickGifts(std::vector<int> &gifts, int k)
    {
        n = gifts.size();
        heapify(gifts);
        while (k--)
        {
            int top = pop(gifts);
            int remain = (int) std::sqrt(top);
            push(gifts, remain);
        }
        return std::accumulate(gifts.begin(), gifts.end(), 0ll);
    }

private:
    int n;

    void heapify(std::vector<int> &array)
    {
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            sink(array, i);
        }
    }

    void sink(std::vector<int> &array, int i)
    {
        while (2 * i + 1 < n)
        {
            int left = 2 * i + 1, right = 2 * i + 2;
            int maxChild = left;
            if (right < n && array[left] < array[right])
                maxChild = right;

            if (array[i] < array[maxChild])
            {
                std::swap(array[i], array[maxChild]);
                i = maxChild;
            }
            else
            {
                break;
            }
        }
    }

    int pop(std::vector<int> &array)
    {
        int top = array[0];
        array[0] = array[--n];
        sink(array, 0);
        return top;
    }

    void push(std::vector<int> &array, int val)
    {
        int i = n++;
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (array[parent] >= val)
                break;
            array[i] = array[parent];
            i = parent;
        }
        array[i] = val;
    }
};

int main()
{
    Solution solution;
    std::vector<int> gifts = {25,64,9,4,100};
    int k = 4;
    long long ans = solution.pickGifts(gifts, k);
    return 0;
}
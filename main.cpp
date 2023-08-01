#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<int> data{0,5,6,10,8,3,2,19,9,11};
    int n = data.size();
    kirie::MinHeap minHeap(n);
    for (int num : data)
    {
        minHeap.push(num);
    }
    while (!minHeap.isEmpty())
    {
        std::cout << minHeap.pop() << std::endl;
    }

    kirie::MaxHeap maxHeap(n);
    for (int num : data)
    {
        maxHeap.push(num);
    }
    while (!maxHeap.isEmpty())
    {
        std::cout << maxHeap.pop() << std::endl;
    }
    return 0;
}

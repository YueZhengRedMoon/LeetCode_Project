#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

namespace Solution1
{
    class SeatManager
    {
    public:
        SeatManager(int n) : minHeap(n), endIter(minHeap.end())
        {
            std::iota(minHeap.begin(), minHeap.end(), 1);
            std::make_heap(minHeap.begin(), minHeap.end(), std::greater<>());
        }

        int reserve()
        {
            int seat = minHeap[0];
            std::pop_heap(minHeap.begin(), endIter--, std::greater<>());
            return seat;
        }

        void unreserve(int seatNumber)
        {
            *endIter++ = seatNumber;
            std::push_heap(minHeap.begin(), endIter, std::greater<>());
        }

    private:
        std::vector<int> minHeap;
        std::vector<int>::iterator endIter;
    };
}

namespace Solution2
{
    class SeatManager
    {
    public:
        SeatManager(int n) : seats(0) {}

        int reserve()
        {
            if (!available.empty())
            {
                int seatNumber = available.top();
                available.pop();
                return seatNumber;
            }
            return ++seats;
        }

        void unreserve(int seatNumber)
        {
            available.push(seatNumber);
        }

    private:
        int seats;
        std::priority_queue<int, std::vector<int>, std::greater<>> available;
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

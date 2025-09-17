#include <iostream>
#include <unordered_map>
#include <queue>

class NumberContainers
{
public:
    using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;

    NumberContainers() = default;

    void change(int index, int number)
    {
        container[index] = number;
        numberIndex[number].push(index);
    }

    int find(int number)
    {
        auto it = numberIndex.find(number);
        if (it == numberIndex.end())
        {
            return -1;
        }

        MinHeap& minHeap = it->second;
        while (!minHeap.empty())
        {
            int index = minHeap.top();
            if (container[index] == number)
            {
                return index;
            }
            else
            {
                minHeap.pop();
            }
        }
        return -1;
    }

private:
    std::unordered_map<int, int> container;
    std::unordered_map<int, MinHeap> numberIndex;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

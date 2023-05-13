#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> rearrangeBarcodes(std::vector<int> &barcodes)
    {
        std::unordered_map<int, int> frequency;
        for (int code : barcodes)
        {
            ++frequency[code];
        }

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> maxHeap;
        for (auto it = frequency.begin(); it != frequency.end(); ++it)
        {
            maxHeap.emplace(it->second, it->first);
        }

        int i = 0;
        while (!maxHeap.empty())
        {
            std::pair<int, int> top1 = maxHeap.top();
            maxHeap.pop();
            barcodes[i++] = top1.second;

            if (!maxHeap.empty())
            {
                std::pair<int, int> top2 = maxHeap.top();
                maxHeap.pop();
                barcodes[i++] = top2.second;

                if (top2.first > 1)
                    maxHeap.emplace(top2.first - 1, top2.second);
            }

            if (top1.first > 1)
                maxHeap.emplace(top1.first - 1, top1.second);
        }

        return barcodes;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
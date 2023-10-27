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

class Solution2
{
public:
    std::vector<int> rearrangeBarcodes(std::vector<int> &barcodes)
    {
        int len = barcodes.size();
        if (len < 2)
        {
            return barcodes;
        }

        std::unordered_map<int, int> counts;
        int maxCount = 0;
        for (int code : barcodes)
        {
            maxCount = std::max(maxCount, ++counts[code]);
        }

        int evenIndex = 0, oddIndex = 1, halfLen = len / 2;
        std::vector<int> ans(len);
        for (auto &[x, cx] : counts)
        {
            while (cx > 0 && cx <= halfLen && oddIndex < len)
            {
                ans[oddIndex] = x;
                --cx;
                oddIndex += 2;
            }
            while (cx > 0)
            {
                ans[evenIndex] = x;
                --cx;
                evenIndex += 2;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
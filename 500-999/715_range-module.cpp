#include <iostream>
#include <map>
#include "../debug/debug.h"

class RangeModule
{
public:
    RangeModule() = default;

    void addRange(int left, int right)
    {
        if (range.empty())
        {
            range[left] = right;
            return;
        }

        // 找到第一个左端点大于left的区间
        auto glIt = range.upper_bound(left);
        if (glIt == range.begin())  // 最左边的区间的左端点就>left，要插入一个新的区间
        {
            int maxRight = right;
            auto it = glIt;
            while (it != range.end() && maxRight >= it->first)
            {
                if (it->second > maxRight)
                    maxRight = it->second;
                auto delIt = it++;
                range.erase(delIt);
            }
            range[left] = maxRight;
        }
        else
        {
            // glIt->firsr > left; prevIt->first <= left
            auto prevIt = glIt;
            --prevIt;
            if (prevIt->second >= left)
            {
                auto it = prevIt;
                int maxRight = right;
                while (it != range.end() && maxRight >= it->first)
                {
                    if (it->second > maxRight)
                        maxRight = it->second;
                    auto delIt = it++;
                    if (delIt != prevIt)
                        range.erase(delIt);
                }
                prevIt->second = maxRight;
            }
            else    // prevIt->second < left
            {
                auto it = glIt;
                int maxRight = right;
                while (it != range.end() && maxRight >= it->first)
                {
                    if (it->second > maxRight)
                        maxRight = it->second;
                    auto delIt = it++;
                    range.erase(delIt);
                }
                range[left] = maxRight;
            }
        }
    }

    bool queryRange(int left, int right)
    {
        if (range.empty())
            return false;

        // 找到第一个左端点>left的区间glIt,glIt的前一个区间是最后一个左端点<= left的区间
        auto glIt = range.upper_bound(left);
        if (glIt == range.begin())
            return false;
        auto prevIt = glIt;
        --prevIt;
        return prevIt->second >= right;
    }

    void removeRange(int left, int right)
    {
        if (range.empty())
            return;

        // 找到第一个左端点>right的区间
        auto grIt = range.upper_bound(right);

        // 所有区间都比待删除区间大
        if (grIt == range.begin())
            return;

        // 删除前面的区间
        auto it = grIt;
        --it;
        while (it->second > left)
        {
            if (it->first < left)
            {
                if (it->second > right)
                {
                    range[right] = it->second;
                }
                it->second = left;
                break;
            }
            else    // it->first >= left
            {
                if (it->second > right)
                {
                    if (it == range.begin())
                    {
                        range[right] = it->second;
                        range.erase(it);
                        break;
                    }
                    else
                    {
                        auto delIt = it--;
                        range[right] = delIt->second;
                        range.erase(delIt);
                    }
                }
                else    // it->second <= right
                {
                    if (it == range.begin())
                    {
                        range.erase(it);
                        break;
                    }
                    else
                    {
                        auto delIt = it--;
                        range.erase(delIt);
                    }
                }
            }
        }
    }

    void printAllRange() const
    {
        for (auto &[left, right] : range)
        {
            std::cout << "[" << left << ", " << right << ") ";
        }
        std::cout << std::endl;
    }

private:
    std::map<int, int> range;   // key:left, value:right
};

int main()
{
    RangeModule rangeModule;
    rangeModule.addRange(10, 30);
    rangeModule.printAllRange();
    rangeModule.removeRange(15, 25);
    rangeModule.printAllRange();
    return 0;
}

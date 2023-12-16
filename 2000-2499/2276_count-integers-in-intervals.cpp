#include <iostream>
#include <map>

class CountIntervals
{
public:
    CountIntervals() : integerCount(0) {}

    void add(int left, int right)
    {
        if (intervals.empty())
        {
            intervals.emplace(left, right);
            integerCount = right - left + 1;
            return;
        }

        // 找到第一个左端点 >= left的区间 interval1
        auto interval1 = intervals.lower_bound(left);

        // 没有区间的左端点 >= left
        if (interval1 == intervals.end())
        {
            // 左端点最大的区间
            auto maxLeftInterval = intervals.rbegin();

            // 左端点最大的区间的右端点小于left，直接插入新增的区间，无需合并
            if (maxLeftInterval->second < left)
            {
                intervals.emplace(left, right);   // 插入新区间
                integerCount += right - left + 1;       // 增加区间包括的整数数
            }
            // 左端点最大的区间的右端点 >= left, < right，合并区间
            else if (maxLeftInterval->second < right)
            {
                integerCount += right - maxLeftInterval->second;
                maxLeftInterval->second = right;
            }
            // 新增的区间已经存在
        }
        // intervals1的左端点 >= left
        else
        {
            if (left < interval1->first)
            {
                // interval1是第一个区间，或interval1的前一个区间的右端点<left，此时需要插入一个新的区间
                auto prev = interval1;
                if (prev != intervals.begin())
                    --prev;
                if (interval1 == intervals.begin() || prev->second < left)
                {
                    // 确定新插入区间的右端点，所有左端点 <= right的区间都要删除
                    auto it = interval1;    // it 指向第一个左端点>left的区间
                    int prevEnd = left - 1;
                    while (it != intervals.end() && it->first <= right)
                    {
                        integerCount += it->first - prevEnd - 1;
                        prevEnd = it->second;
                        auto delIt = it;
                        ++it;
                        intervals.erase(delIt);
                    }
                    if (right > prevEnd)
                    {
                        integerCount += right - prevEnd;
                        intervals.emplace(left, right);
                    }
                    else
                    {
                        intervals.emplace(left, prevEnd);
                    }
                }
                // interval1前面有区间，且前一个区间的右端点>=left，此时需要合并区间
                else
                {
                    // 确定prev区间扩充后的右端点，并删除被合并的区间，所以左端点<=right的区间都将被合并
                    auto it = interval1;
                    int prevEnd = prev->second;
                    while (it != intervals.end() && it->first <= right)
                    {
                        integerCount += it->first - prevEnd - 1;
                        prevEnd = it->second;
                        auto delIt = it;
                        ++it;
                        intervals.erase(delIt);
                    }
                    if (right > prevEnd)
                    {
                        integerCount += right - prevEnd;
                        prev->second = right;
                    }
                    else
                    {
                        prev->second = prevEnd;
                    }
                }
            }
            // left == interval1的左端点
            else
            {
                // 合并区间，所有左端点<=right的区间都将被合并
                auto it = interval1;
                ++it;
                int prevEnd = interval1->second;
                while (it != intervals.end() && it->first <= right)
                {
                    integerCount += it->first - prevEnd - 1;
                    prevEnd = it->second;
                    auto delIt = it;
                    ++it;
                    intervals.erase(delIt);
                }
                if (right > prevEnd)
                {
                    integerCount += right - prevEnd;
                    interval1->second = right;
                }
                else
                {
                    interval1->second = prevEnd;
                }
            }
        }
    }

    int count()
    {
        return integerCount;
    }

    void print()
    {
        for (auto [left, right] : intervals)
        {
            std::cout << '[' << left << ", " << right << "] ";
        }
        std::cout << std::endl;
    }

private:
    std::map<int, int> intervals;
    int integerCount;
};

int main()
{
    CountIntervals countIntervals;
    countIntervals.add(2, 3);
    countIntervals.print();
    std::cout << countIntervals.count() << std::endl;

    countIntervals.add(7, 10);
    countIntervals.print();
    std::cout << countIntervals.count() << std::endl;

    countIntervals.add(5, 8);
    countIntervals.print();
    std::cout << countIntervals.count() << std::endl;
    return 0;
}
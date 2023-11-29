#include <iostream>
#include <bitset>
#include <vector>
#include <queue>

namespace Solution1
{
    class SmallestInfiniteSet
    {
    public:
        SmallestInfiniteSet() {}

        int popSmallest()
        {
            if (missingNum.none())
            {
                missingNum.set(1);
                return 1;
            }
            else
            {
                for (int i = 1; i < MAX_NUM; ++i)
                {
                    if (!missingNum[i])
                    {
                        missingNum.set(i);
                        return i;
                    }
                }
            }
            return 0;
        }

        void addBack(int num)
        {
            missingNum.reset(num);
        }

    private:
        static constexpr int MAX_NUM = 1001;
        std::bitset<MAX_NUM> missingNum;
    };
}

class SmallestInfiniteSet
{
public:
    SmallestInfiniteSet() : inSet(1001, false), idx(1) {}

    int popSmallest()
    {
        int res = -1;
        if (!minHeap.empty())   // 存在被弹出后又被加入到无限集中，且<idx-1的数
        {
            // 返回其中最小的数
            res = minHeap.top();
            minHeap.pop();
            inSet[res] = false;   // 标记该数已经不在无限集中
        }
        else
        {
            res = idx++;
        }
        return res;
    }

    void addBack(int num)
    {
        if (num >= idx || inSet[num])
            return;
        if (num == idx - 1)
        {
            --idx;
        }
        else
        {
            minHeap.push(num);
            inSet[num] = true;
        }
    }

private:
    std::vector<bool> inSet;
    std::priority_queue<int, std::vector<int>, std::greater<>> minHeap; // 小顶堆中存放着被弹出无限集，又被加入到无限集中的数
    int idx;    // 待弹出数[idx, inf)的左边界
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

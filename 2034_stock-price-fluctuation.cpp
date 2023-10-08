#include <iostream>
#include <set>
#include <unordered_map>

class StockPrice
{
public:
    StockPrice() : currentTime(0) {}

    void update(int timestamp, int price)
    {
        // 时间戳第一次出现
        auto psItMapIter = psItMap.find(timestamp);
        if (psItMapIter == psItMap.end())
        {
            auto psIt = priceSet.emplace(price);
            psItMap[timestamp] = psIt;
            // 更新当前时间
            if (timestamp > currentTime)
                currentTime = timestamp;
        }
        // 时间戳已经出现过，更新它
        else
        {
            auto oldPsIt = psItMapIter->second;
            priceSet.erase(oldPsIt);
            auto newPtIt = priceSet.emplace(price);
            psItMapIter->second = newPtIt;
        }
    }

    int current()
    {
        return *psItMap[currentTime];
    }

    int maximum()
    {
        return *priceSet.crbegin();
    }

    int minimum()
    {
        return *priceSet.cbegin();
    }

private:
    // 股票价格有序集合
    std::multiset<int> priceSet;
    // key:time, value:priceSet::iterator
    std::unordered_map<int, std::multiset<int>::iterator> psItMap;
    // 当前时间
    int currentTime;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

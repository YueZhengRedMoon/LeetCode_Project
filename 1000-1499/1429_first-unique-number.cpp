#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

class FirstUnique
{
public:
    FirstUnique(std::vector<int> &nums)
    {
        for (int num : nums)
        {
            add(num);
        }
    }

    int showFirstUnique()
    {
        if (queue.empty())
        {
            return -1;
        }
        return queue.front();
    }

    void add(int value)
    {
        auto mapIter = iterMap.find(value);
        if (mapIter == iterMap.end())
        {
            queue.push_back(value);
            std::list<int>::iterator listIter = queue.end();
            --listIter;
            iterMap[value] = std::make_pair(listIter, true);
        }
        else
        {
            if (mapIter->second.second)
            {
                queue.erase(mapIter->second.first);
                mapIter->second.second = false;
            }
        }
    }

private:
    std::list<int> queue;
    std::unordered_map<int, std::pair<std::list<int>::iterator, bool>> iterMap;
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

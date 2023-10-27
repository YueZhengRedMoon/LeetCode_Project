#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

class TimeMap2
{
public:
    TimeMap2() {}

    void set(std::string key, std::string value, int timestamp)
    {
        map[key].emplace(timestamp, value);
    }

    std::string get(std::string key, int timestamp)
    {
        auto it1 = map.find(key);
        if (it1 == map.end())
            return "";

        std::map<int, std::string> &timeMap = it1->second;
        auto it2 = timeMap.lower_bound(timestamp);

        if (it2 == timeMap.end())
        {
            --it2;
            return it2->second;
        }
        if (it2->first == timestamp)
        {
            return it2->second;
        }
        if (it2 == timeMap.begin())
        {
            return "";
        }
        else
        {
            --it2;
            return it2->second;
        }
    }

private:
    std::unordered_map<std::string, std::map<int, std::string>> map;
};

class TimeMap
{
public:
    TimeMap() {}

    void set(std::string key, std::string value, int timestamp)
    {
        map[key].emplace_back(timestamp, value);
    }

    std::string get(std::string key, int timestamp)
    {
        auto mapIt = map.find(key);
        if (mapIt == map.end())
            return "";

        std::vector<std::pair<int, std::string>> &values = mapIt->second;
        int n = values.size();
        // 在values中找到最大的first <= timestamp的元素
        int left = 0, right = n, index = -1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (values[mid].first <= timestamp)
            {
                index = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return index == -1 ? "" : values[index].second;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> map;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <deque>
#include <tuple>
#include <algorithm>

class Router
{
public:
    Router(int memoryLimit) : limit(memoryLimit)
    {

    }

    bool addPacket(int source, int destination, int timestamp)
    {
        std::string packetHash = hash(source, destination, timestamp);
        if (packetSet.find(packetHash) != packetSet.end())
        {
            // 重复的数据包
            return false;
        }

        if (packetQueue.size() >= limit)
        {
            forwardPacket();
        }

        packetQueue.emplace_back(source, destination, timestamp);
        packetSet.insert(packetHash);
        desMap[destination].emplace_back(timestamp);
        return true;
    }

    std::vector<int> forwardPacket()
    {
        if (packetQueue.empty())
        {
            return {};
        }

        auto [src, des, time] = packetQueue.front();
        packetQueue.pop_front();
        desMap[des].pop_front();
        packetSet.erase(hash(src, des, time));
        return {src, des, time};
    }

    int getCount(int destination, int startTime, int endTime)
    {
        auto it = desMap.find(destination);
        if (it == desMap.end())
        {
            return 0;
        }

        const std::deque<int>& timestamps = it->second;
        return std::upper_bound(timestamps.begin(), timestamps.end(), endTime) - std::lower_bound(timestamps.begin(), timestamps.end(), startTime);
    }

private:
    std::unordered_set<std::string> packetSet;
    std::deque<std::tuple<int, int, int>> packetQueue;
    std::unordered_map<int, std::deque<int>> desMap;
    int limit;

    std::string hash(int source, int destination, int timestamp)
    {
        return std::to_string(source) + ";" + std::to_string(destination) + ";" + std::to_string(timestamp);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

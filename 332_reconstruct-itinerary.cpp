#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>

/** 错误 */
class Solution
{
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> &tickets)
    {
        std::sort(tickets.begin(), tickets.end(), less);

        std::unordered_map<int, int> startIndex;
        int lastKey = 0;
        for (int i = 0; i < tickets.size(); ++i)
        {
            int key = getKey(tickets[i][0]);
            if (key != lastKey)
            {
                startIndex[key] = i;
            }
            lastKey = key;
        }

        std::vector<std::string> result = {"JFK"};
        std::vector<bool> used(tickets.size(), false);
        int index = startIndex[getKey("JFK")];
        int usedNums = 0;
        while (usedNums < tickets.size())
        {
            int targetKey = getKey(tickets[index][1]);
            if (!used[index] && (startIndex.find(targetKey) != startIndex.end() || usedNums + 1 == tickets.size()))
            {
                result.push_back(tickets[index][1]);
                used[index] = true;
                ++usedNums;
                index = startIndex[getKey(tickets[index][1])];
            }
            else
            {
                if (index + 1 < tickets.size())
                {
                    ++index;
                }
                else
                {
                    index = startIndex[getKey(tickets[index][1])];
                }
            }
        }

        return result;
    }

private:
    static bool less(const std::vector<std::string> &lhs, const std::vector<std::string> &rhs)
    {
        int result = lhs[0].compare(rhs[0]);
        if (result == 0)
        {
            result = lhs[1].compare(rhs[1]);
        }
        return result < 0;
    }

    inline int getKey(const std::string &str)
    {
        return str[0] * 0x10000 + str[1] * 0x100 + str[2];
    }
};

class Solution2
{
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> &tickets)
    {
        std::vector<std::string> result;
        for (const auto& ticket : tickets)
        {
            ++targets[ticket[0]][ticket[1]];
        }
        result.push_back("JFK");
        backtracking(tickets.size(), result);
        return result;
    }

private:
    // unordered_map<出发机场， map<到达机场，航班次数>>
    std::unordered_map<std::string, std::map<std::string, int>> targets;

    bool backtracking(int ticketNum, std::vector<std::string> &result)
    {
        if (result.size() == ticketNum + 1)
        {
            return true;
        }

        for (auto &target : targets[result.back()])
        {
            if (target.second > 0)
            {
                result.push_back(target.first);
                --target.second;
                if (backtracking(ticketNum, result))
                {
                    return true;
                }
                result.pop_back();
                ++target.second;
            }
        }

        return false;
    }
};

int main()
{
    std::vector<std::vector<std::string>> tickets = {{"EZE","TIA"},{"EZE","HBA"},{"AXA","TIA"},{"JFK","AXA"},
                                                     {"ANU","JFK"},{"ADL","ANU"},{"TIA","AUA"},{"ANU","AUA"},
                                                     {"ADL","EZE"},{"ADL","EZE"},{"EZE","ADL"},{"AXA","EZE"},
                                                     {"AUA","AXA"},{"JFK","AXA"},{"AXA","AUA"},{"AUA","ADL"},
                                                     {"ANU","EZE"},{"TIA","ADL"},{"EZE","ANU"},{"AUA","ANU"}};
    Solution2 solution;
    std::vector<std::string> result = solution.findItinerary(tickets);
    for (const auto& str : result)
    {
        std::cout << str << ' ';
    }
    std::cout << std::endl;
    return 0;
}
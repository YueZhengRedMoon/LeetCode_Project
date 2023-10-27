#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>


class Solution
{
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> &tickets)
    {
        for (const auto& ticket : tickets)
        {
            ++targets[ticket[0]][ticket[1]];
        }

        std::vector<std::string> result = {"JFK"};
        backtracking(tickets.size() + 1, result);
        return result;
    }

private:
    /** 出发机场 <目的机场，机票数> */
    std::unordered_map<std::string, std::map<std::string, int, std::less<>>> targets;

    bool backtracking(int ticketsNum, std::vector<std::string> &result)
    {
        if (result.size() == ticketsNum)
        {
            return true;
        }

        for (auto &target : targets[result.back()])
        {
            if (target.second > 0)
            {
                result.push_back(target.first);
                --target.second;
                if (backtracking(ticketsNum, result))
                {
                    return true;
                }
                ++target.second;
                result.pop_back();
            }
        }

        return false;
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
    Solution2 solution2;
    std::vector<std::string> result2 = solution2.findItinerary(tickets);
    for (const auto& str : result2)
    {
        std::cout << str << ' ';
    }
    std::cout << std::endl;

    Solution solution1;
    std::vector<std::string> result1 = solution1.findItinerary(tickets);
    for (const auto& str : result1)
    {
        std::cout << str << ' ';
    }
    return 0;
}
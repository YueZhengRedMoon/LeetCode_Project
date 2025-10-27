#include <iostream>
#include <vector>
#include <string>
#include <map>

class Solution
{
public:
    bool hasSameDigits(std::string s)
    {
        return false;
    }
};

int main()
{
    using Pair = std::pair<int, int>;
    std::string s = "3478934789";
    std::vector<std::map<int, int>> line;
    for (int i = 0; i < s.size(); ++i)
    {
        std::map<int, int> elem;
        elem.emplace(i, 1);
        line.push_back(elem);
    }
    int lineSize = line.size();
    while (lineSize >= 2)
    {
        std::string t;
        for (const std::map<int, int>& elem : line)
        {
            for (auto& [idx, cnt] : elem)
            {
                t += "<" + std::to_string(cnt) + ", " + std::to_string(idx) + ">+";
            }
            t.back() = ' ';
        }
        std::cout << t << "\n===========================" << std::endl;

        std::vector<std::map<int, int>> nextLine;
        nextLine.reserve(lineSize - 1);
        for (int i = 0; i < lineSize - 1; ++i)
        {
            std::map<int, int> newElem = line[i];
            for (auto it = line[i + 1].begin(); it != line[i + 1].end(); ++it)
            {
                auto& [idx, cnt] = *it;
                newElem[idx] += cnt;
            }
            nextLine.push_back(newElem);
        }
        std::swap(line, nextLine);
        --lineSize;
    }
    return 0;
}
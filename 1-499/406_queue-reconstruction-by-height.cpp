#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

class Solution
{
public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>> &people)
    {
        std::sort(people.begin(), people.end(), greater);
        std::list<std::vector<int>> list;
        for (auto &entry : people)
        {
            int h = entry[0];
            int k = entry[1];
            auto it = list.begin();
            for (int i = 0; i < k; ++i)
            {
                ++it;
            }
            list.insert(it, {h, k});
        }
        std::vector<std::vector<int>> queue;
        queue.reserve(people.size());
        for (auto &entry : list)
        {
            queue.push_back(entry);
        }
        return queue;
    }

private:
    static bool greater(const std::vector<int> &lhs, const std::vector<int> &rhs)
    {
        if (lhs[0] == rhs[0])
        {
            return lhs[1] < rhs[1];
        }
        return lhs[0] > rhs[0];
    }
};

int main()
{
    std::vector<std::vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    Solution solution;
    std::vector<std::vector<int>> queue = solution.reconstructQueue(people);
    for (const auto &entry : queue)
    {
        std::cout << '[' << entry[0] << ", " << entry[1] << "] ";
    }
    std::cout << std::endl;
    return 0;
}
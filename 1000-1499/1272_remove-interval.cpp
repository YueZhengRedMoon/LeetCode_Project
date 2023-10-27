#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> removeInterval(std::vector<std::vector<int>> &intervals, std::vector<int> &toBeRemoved)
    {
        std::vector<std::vector<int>> ans;
        for (const std::vector<int> &interval : intervals)
        {
            // 当前集合与待删除集合没有交集
            if (interval[0] >= toBeRemoved[1] || interval[1] <= toBeRemoved[0])
            {
                ans.push_back(interval);
            }
            // 当前集合包含了待删除集合
            else if (interval[0] < toBeRemoved[0] && interval[1] > toBeRemoved[1])
            {
                ans.push_back({interval[0], toBeRemoved[0]});
                ans.push_back({toBeRemoved[1], interval[1]});
            }
            // 当前集合的右半部分与待删除集合有交集
            else if (interval[0] < toBeRemoved[0] && interval[1] > toBeRemoved[0])
            {
                ans.push_back({interval[0], toBeRemoved[0]});
            }
            // 当前集合的左半部分与待删除的集合有交集
            else if (interval[0] < toBeRemoved[1] && interval[1] > toBeRemoved[1])
            {
                ans.push_back({toBeRemoved[1], interval[1]});
            }
            // else,当前集合是待删除集合的子集
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

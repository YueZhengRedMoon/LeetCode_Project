#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> highFive(std::vector<std::vector<int>> &items)
    {
        std::sort(items.begin(), items.end(), [](const std::vector<int> &lhs, const std::vector<int> &rhs) {
            if (lhs[0] == rhs[0])
                return lhs[1] > rhs[1];
            return lhs[0] < rhs[0];
        });
        std::vector<std::vector<int>> ans;
        int id = items[0][0], count = 0, sum = 0;
        for (const std::vector<int> &item : items)
        {
            if (count >= 5)
            {
                if (item[0] != id)
                {
                    count = 1;
                    sum = item[1];
                    id = item[0];
                }
            }
            else
            {
                ++count;
                sum += item[1];
                if (count == 5)
                {
                    ans.push_back({id, sum / 5});
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <map>

class Solution
{
public:
    int largestUniqueNumber(std::vector<int> &nums)
    {
        std::map<int, int, std::greater<>> count;
        for (int num : nums)
        {
            ++count[num];
        }
        for (auto it = count.begin(); it != count.end(); ++it)
        {
            if (it->second == 1)
                return it->first;
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

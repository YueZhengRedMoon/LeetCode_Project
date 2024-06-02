#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int distributeCandies(std::vector<int>& candyType)
    {
        int n = candyType.size();
        std::unordered_set<int> set(candyType.begin(), candyType.end());
        return std::min<int>(set.size(), n / 2);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <string_view>
#include <unordered_map>

class Solution
{
public:
    int minimumOperationsToMakeKPeriodic(std::string word, int k)
    {
        int n = word.size(), maxCnt;
        std::unordered_map<std::string_view, int> counter;
        for (int i = 0; i < n; i += k)
        {
            std::string_view s(word.data() + i, k);
            maxCnt = std::max(maxCnt, ++counter[s]);
        }
        return (n / k) - maxCnt;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

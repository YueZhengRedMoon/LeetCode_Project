#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int maxFrequencyElements(std::vector<int>& nums)
    {
        std::unordered_map<int, int> counter;
        int maxFreq = 0;
        for (int x : nums)
        {
            ++counter[x];
            if (counter[x] > maxFreq)
            {
                maxFreq = counter[x];
            }
        }

        int ans = 0;
        for (auto it = counter.begin(); it != counter.end(); ++it)
        {
            if (it->second == maxFreq)
            {
                ans += maxFreq;
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

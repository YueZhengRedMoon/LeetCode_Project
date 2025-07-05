#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int findLucky(std::vector<int>& arr)
    {
        std::unordered_map<int, int> freq;
        for (int x : arr)
        {
            ++freq[x];
        }

        int ans = -1;
        for (auto it = freq.begin(); it != freq.end(); ++it)
        {
            if (it->first == it->second && it->first > ans)
                ans = it->first;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

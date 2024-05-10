#include <iostream>
#include <vector>

class Solution
{
public:
    int garbageCollection(std::vector<std::string>& garbage, std::vector<int>& travel)
    {
        int n = garbage.size(), lastM = -1, lastP = -1, lastG = -1;
        for (int i = 0; i < n; ++i)
        {
            for (char c : garbage[i])
            {
                if (c == 'M')
                    lastM = i;
                else if (c == 'P')
                    lastP = i;
                else
                    lastG = i;
            }
        }

        int ans = garbage[0].size();
        for (int i = 1; i < n; ++i)
        {
            ans += garbage[i].size() + travel[i - 1] * ((lastM >= i) + (lastG >= i) + (lastP >= i));
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

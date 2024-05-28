#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findPeaks(std::vector<int>& mountain)
    {
        int n = mountain.size();
        std::vector<int> ans;
        for (int i = 1; i < n - 1; ++i)
        {
            if (mountain[i - 1] < mountain[i] && mountain[i] > mountain[i + 1])
            {
                ans.push_back(i);
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

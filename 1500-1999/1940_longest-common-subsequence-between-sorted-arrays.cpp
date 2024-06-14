#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> longestCommonSubsequence(std::vector<std::vector<int>>& arrays)
    {
        int n = arrays.size();
        std::vector<std::vector<int>::iterator> begins(n);
        for (int i = 0; i < n; ++i)
        {
            begins[i] = arrays[i].begin();
        }

        std::vector<int> ans;
        for (int x : arrays[0])
        {
            bool common = true;
            for (int i = 1; i < n && common; ++i)
            {
                begins[i] = std::lower_bound(begins[i], arrays[i].end(), x);
                if (begins[i] == arrays[i].end())
                {
                    return ans;
                }
                common = (*begins[i] == x);
            }
            if (common)
                ans.push_back(x);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

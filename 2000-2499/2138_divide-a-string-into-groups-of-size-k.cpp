#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::string> divideString(std::string s, int k, char fill)
    {
        int n = s.size();
        std::vector<std::string> ans((n + k - 1) / k, std::string(k, fill));

        for (int i = 0; i * k < n; ++i)
        {
            for (int j = 0; j < k && i * k + j < n; ++j)
            {
                ans[i][j] = s[i * k + j];
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

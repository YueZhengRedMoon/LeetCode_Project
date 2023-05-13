#include <iostream>
#include <vector>

class Solution
{
public:
    int maxArea(std::vector<int> &height)
    {
        int i = 0, j = height.size() - 1, res = 0;
        while(i < j) {
            res = height[i] < height[j] ?
                  std::max(res, (j - i) * height[i++]):
                  std::max(res, (j - i) * height[j--]);

            std::cout << res << std::endl;
        }
        return res;
    }
};

int main()
{
    std::vector<int> height = {1,3,2,5,25,24,5};
    Solution solution;
    int result = solution.maxArea(height);
    std::cout << result << std::endl;
    return 0;
}

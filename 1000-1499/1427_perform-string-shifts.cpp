#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::string stringShift(std::string s, std::vector<std::vector<int>> &shifts)
    {
        int finalShift = 0; // 最终移动的位数，正数表示右移，负数表示左移
        for (const auto &shift : shifts)
        {
            if (shift[0] == 0)  // 左移
                finalShift -= shift[1];
            else                // 右移
                finalShift += shift[1];
        }
        int len = s.size();
        finalShift %= len;
        int amount = 0;
        if (finalShift > 0) // 最终右移
        {
            amount = len - finalShift;
        }
        else if (finalShift < 0)    // 最终左移
        {
            amount = -finalShift;
        }
        else
        {
            return s;
        }
        std::reverse(s.begin(), s.begin() + amount);
        std::reverse(s.begin() + amount, s.end());
        std::reverse(s.begin(), s.end());
        return s;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
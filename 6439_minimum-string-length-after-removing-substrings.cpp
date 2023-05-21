#include <iostream>
#include <vector>

class Solution
{
public:
    int minLength(std::string s)
    {
        int n = s.size();
        std::vector<char> stack(n);
        int top = -1;
        for (int i = 0; i < n; ++i)
        {
            stack[++top] = s[i];
            while (top >= 1 && ((stack[top - 1] == 'A' && stack[top] == 'B') || (stack[top - 1] == 'C' && stack[top] == 'D')))
            {
                top -= 2;
            }
        }
        return top + 1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

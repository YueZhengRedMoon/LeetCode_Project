#include <iostream>
#include <vector>
#include <stack>
#include "debug.h"

class Solution
{
public:
    bool canChange(std::string start, std::string target)
    {
        int n = start.size();

        std::stack<int> leftStack, rightStack, leftStack2, rightStack2;
        bool equal = true;
        for (int i = n - 1; i >= 0 ; --i)
        {
            if (start[i] == 'L')
            {
                leftStack.push(i);
            }
            else if (start[i] == 'R')
            {
                rightStack.push(i);
            }
            if (start[i] != target[i])
            {
                equal = false;
            }
        }

        if (equal)
            return true;

        for (int i = 0; i < n; ++i)
        {
            if (start[i] == 'R')
            {
                rightStack2.push(i);
                rightStack.pop();
            }

            // 遇到L，检查右边是否有L可以左移过来
            if (target[i] == 'L')
            {
                if (leftStack.empty() || leftStack.top() < i || (!rightStack.empty() && rightStack.top() < leftStack.top()))
                {
                    // 没有L可以左移过来
                    // 最左边的L在当前L的左边
                    // 有R挡在了最左边的L的左边
                    return false;
                }
                else
                {
                    // 匹配成功，消去最左边的L
                    leftStack2.push(leftStack.top());
                    leftStack.pop();
                }
            }
            // 遇到R，检查左边是否有R可以右移过来
            else if (target[i] == 'R')
            {
                if (rightStack2.empty() || (!leftStack2.empty() && leftStack2.top() > rightStack2.top()))
                {
                    // 没有R可以右移过来
                    // 有L挡在了最右边的R的右边
                    return false;
                }
                else
                {
                    rightStack2.pop();
                }
            }
        }
        return leftStack.empty() && rightStack2.empty();
    }
};

int main()
{
    Solution solution;
    std::string start = "__R_R_R_L", target = "____RRR_L";
    bool ans = solution.canChange(start, target);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}

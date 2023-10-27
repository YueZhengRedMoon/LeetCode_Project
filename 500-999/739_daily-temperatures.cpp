#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> dailyTemperatures(std::vector<int> &temperatures)
    {
        std::vector<int> answer(temperatures.size(), 0);
        std::stack<int> stack;
        for (int i = 0; i < temperatures.size(); ++i)
        {
            while (!stack.empty() && temperatures[i] > temperatures[stack.top()])
            {
                int top = stack.top();
                stack.pop();
                answer[top] = i - top;
            }
            stack.push(i);
        }
        return answer;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

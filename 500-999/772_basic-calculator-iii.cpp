#include <iostream>
#include <vector>

class Solution
{
public:
    int calculate(std::string s)
    {
        std::vector<int> numStack;   // 操作数栈
        std::vector<char> opStack;   // 操作符栈
        int n = s.size(), i = 0;
        while (i < n)
        {
            if (std::isdigit(s[i])) // 操作数
            {
                // 将字符串转为操作数
                int num = s[i++] - '0';
                while (i < n && std::isdigit(s[i]))
                {
                    num = num * 10 + (s[i++] - '0');
                }
                // 将操作数入栈
                pushNum(numStack, opStack, num);
            }
            else    // 操作符
            {
                if (s[i] == ')')
                {
                    // 找到匹配的'('，计算括号内的值，然后将结果放入操作数栈
                    calculate(numStack, opStack);
                }
                else
                {
                    // 将操作符入栈
                    opStack.push_back(s[i]);
                }
                ++i;
            }
        }
        // 计算剩余的表达式
        calculate(numStack, opStack);
        return numStack.back(); // 表达式计算完成后，栈顶即为结果
    }

private:
    // 从符号栈中获取操作符，从操作数栈中获取操作数
    char getOpAndNum(std::vector<int>& numStack, std::vector<char>& opStack, int& lhs, int &rhs)
    {
        char op = opStack.back();
        opStack.pop_back();

        rhs = numStack.back();
        numStack.pop_back();
        lhs = numStack.back();
        numStack.pop_back();

        return op;
    }

    // 计算lhs op rhs
    int calculate(int lhs, char op, int rhs)
    {
        int res = -1;
        switch (op)
        {
            case '+':
                res = lhs + rhs;
                break;
            case '-':
                res = lhs - rhs;
                break;
            case '*':
                res = lhs * rhs;
                break;
            case '/':
                res = lhs / rhs;
                break;
        }
        return res;
    }

    // 按照从左到右的顺序计算栈中可计算的部分
    // 可计算部分的形式为:num_1 op_1 num_2 op_2 num_3 ... num_n-1 op_n-1 num_n
    // 或者有一个左括号:(num_1 op_1 num_2 op_2 num_3 ... num_n-1 op_n-1 num_n
    // 其中op一定为'+'或'-'
    void calculate(std::vector<int>& numStack, std::vector<char>& opStack)
    {
        int numStackSize = numStack.size(), opStackSize = opStack.size(), i, j;
        for (i = opStackSize - 1; i >= 0 && opStack[i] != '('; --i);    // 循环结束后i+1指向第1个操作符
        int opCnt = opStackSize - i - 1;    // 操作符的个数
        int numCnt = opCnt + 1;             // 操作数的个数

        int lhs = numStack[numStackSize - numCnt];
        for (i = i + 1, j = numStackSize - numCnt + 1; i < opStackSize && j < numStackSize; ++i, ++j)
        {
            int rhs = numStack[j];
            lhs = calculate(lhs, opStack[i], rhs);
        }   // 循环结束后,lhs即为表达式的值

        numStack.resize(numStackSize - numCnt); // 所有操作数出栈
        opStack.resize(opStackSize - opCnt);    // 所有操作符出栈

        // 如果有左括号，则将其出栈
        if (!opStack.empty() && opStack.back() == '(')
            opStack.pop_back();

        // 将结果重新放入操作数栈，如果符号栈栈顶为'*'或'/'，则刚入栈的数为右操作数，进行相应的运算，并将计算的结果放入操作数栈
        pushNum(numStack, opStack, lhs);
    }

    // 将num push到操作数栈中，如果符号栈栈顶为'*'或'/'，则入栈的数是右操作数，进行相应的运算，并将计算的结果放入操作数栈
    void pushNum(std::vector<int>& numStack, std::vector<char>& opStack, int num)
    {
        numStack.push_back(num);

        if (!opStack.empty() && (opStack.back() == '*' || opStack.back() == '/'))
        {
            int lhs, rhs, res;
            char op = getOpAndNum(numStack, opStack, lhs, rhs);
            res = calculate(lhs, op, rhs);
            numStack.push_back(res);
        }
    }
};

int main()
{
    Solution solution;
    std::string s = "1*2-3/4+5*6-7*8+9/10";
    int ans = solution.calculate(s);
    std::cout << ans << std::endl;
    return 0;
}

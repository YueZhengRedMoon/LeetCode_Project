#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool judgePoint24(std::vector<int>& cards)
    {
        std::string expression = "0000000";
        char op[4] = {'+', '-', '*', '/'};
        std::sort(cards.begin(), cards.end());
        while (std::next_permutation(cards.begin(), cards.end()))
        {
            // 构造表达式
            for (int i = 0, j = 0; i < 4; ++i, j += 2)
                expression[j] = cards[i];
            for (int op1 = 0; op1 < 4; ++op1)
            {
                for (int op3 = 0; op3 < 4; ++op3)
                {
                    for (int op5 = 0; op5 < 4; ++op5)
                    {
                        expression[1] = op[op1];
                        expression[3] = op[op3];
                        expression[5] = op[op5];

                        if (check(expression))
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

private:
    bool check(const std::string& expr)
    {
        // calc(calc(expr, 2, 4), calc(6, 6), expr[5])
        return  is24(calc(expr, 0, 6)) ||
                is24(calc(calc(expr, 0, 0), calc(expr, 2, 6), expr[1])) ||
                is24(calc(calc(expr, 0, 4), calc(expr, 6, 6), expr[5])) ||
                is24(calc(calc(expr, 0, 2), calc(expr, 4, 6), expr[3])) ||
                is24(calc(calc(calc(expr, 0, 0), calc(expr, 2, 4), expr[1]), calc(expr, 6, 6), expr[5])) ||
                is24(calc(calc(expr, 0, 0), calc(calc(expr, 2, 4), calc(expr, 6, 6), expr[5]), expr[1])) ||
                is24(calcReverse(expr, 0, 6));
    }

    std::pair<int, int> calc(const std::string& expression, int i, int j)
    {
        int a = expression[i] - '0', b = 1;   // a:分子, b:分母
        for (int k = i + 2; k <= j; k += 2)
        {
            int x = expression[k] - '0';
            switch (expression[k - 1])
            {
                case '+':
                    a += b * x;
                    break;
                case '-':
                    a -= b * x;
                    break;
                case '*':
                    a *= x;
                case '/':
                    b *= x;
                    break;
                default:
                    break;
            }
        }
        return {a, b};
    }

    std::pair<int, int> calcReverse(const std::string& expression, int i, int j)
    {
        int a = expression[j] - '0', b = 1;   // a:分子, b:分母
        for (int k = j - 2; k >= i; k -= 2)
        {
            int x = expression[k] - '0';
            switch (expression[k + 1])
            {
                case '+':
                    a += b * x;
                    break;
                case '-':
                    a -= b * x;
                    break;
                case '*':
                    a *= x;
                case '/':
                    b *= x;
                    break;
                default:
                    break;
            }
        }
        return {a, b};
    }

    std::pair<int, int> calc(const std::pair<int, int>& x1, const std::pair<int, int>& x2, char op)
    {
        int a1 = x1.first, b1 = x1.second, a2 = x2.first, b2 = x2.second;
        if (op == '+')
            return {a1 * b2 + a2 * b1, b1 * b2};
        else if (op == '-')
            return {a1 * b2 - a2 * b1, b1 * b2};
        else if (op == '*')
            return {a1 * a2, b1 * b2};
        else
            return {a1 * b2, b1 * a2};
    }

    // 判断分式是否是24
    bool is24(const std::pair<int, int>& x)
    {
        return x.second != 0 && x.first % x.second == 0 && x.first / x.second == 24;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

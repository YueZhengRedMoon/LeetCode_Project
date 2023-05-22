#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    std::vector<int> diffWaysToCompute(std::string expression)
    {
        if (expression[0] == '-') expression[0] = 'n';
        int opCount = std::count_if(expression.begin() + 1, expression.end(), [](char c) {return !isdigit(c);});
        backtracking(expression, opCount);
        std::vector<int> ans(resultSet.begin(), resultSet.end());
        return ans;
    }

private:
    std::unordered_set<std::string> memo;
    std::unordered_set<int> resultSet;

    void backtracking(std::string expression, int opCount)
    {
        if (!memo.insert(expression).second)
        {
            return;
        }
        if (opCount == 0)
        {
            if (expression[0] == 'n') expression[0] = '-';
            int result = std::stoi(expression);
            resultSet.insert(result);
            return;
        }
        // 用'n'表示负号
        int len = expression.size();
        for (int i = 1; i < len - 1; ++i)
        {
            if (std::isdigit(expression[i]) || expression[i] == 'n') continue;

            int lhsStart = i, lhsLen = 0;
            while (lhsStart - 1 >= 0 && (std::isdigit(expression[lhsStart - 1]) || expression[lhsStart - 1] == 'n'))
            {
                --lhsStart;
                ++lhsLen;
            }
            std::string lhsStr = expression.substr(lhsStart, lhsLen);
            if (lhsStr[0] == 'n') lhsStr[0] = '-';
            int lhs = std::stoi(lhsStr);

            int rhsStart = i + 1, rhsLen = 1;
            while (rhsStart + rhsLen < len && std::isdigit(expression[rhsStart + rhsLen]))
            {
                ++rhsLen;
            }
            std::string rhsStr = expression.substr(rhsStart, rhsLen);
            if (rhsStr[0] == 'n') rhsStr[0] = '-';
            int rhs = std::stoi(rhsStr);

            int opRes;
            switch (expression[i])
            {
                case '+':
                    opRes = lhs + rhs;
                    break;
                case '-':
                    opRes = lhs - rhs;
                    break;
                case '*':
                    opRes = lhs * rhs;
                    break;
            }
            std::string opResStr = std::to_string(opRes);
            if (opRes < 0) opResStr[0] = 'n';

            std::string newExpr = expression.substr(0, lhsStart) + opResStr + expression.substr(rhsStart + rhsLen);
            backtracking(newExpr, opCount - 1);
        }
    }
};

int main()
{
    Solution solution;
    std::string expression = "2*3-4*5";
    std::vector<int> ans = solution.diffWaysToCompute(expression);
    debug::printVector(ans);
    return 0;
}

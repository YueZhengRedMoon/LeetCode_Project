#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "../debug/debug.h"

/** 错误 */
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

class Solution2
{
public:
    using Vector3D = std::vector<std::vector<std::vector<int>>>;

    std::vector<int> diffWaysToCompute(std::string expression)
    {
        int exprLen = expression.size();
        std::vector<int> ops;
        for (int i = 0; i < exprLen;)
        {
            if (expression[i] == '+')
            {
                ops.push_back(ADD);
                ++i;
            }
            else if (expression[i] == '-')
            {
                ops.push_back(SUB);
                ++i;
            }
            else if (expression[i] == '*')
            {
                ops.push_back(MUL);
                ++i;
            }
            else
            {
                int t = 0;
                while (i < exprLen && std::isdigit(expression[i]))
                {
                    t = t * 10 + (expression[i] - '0');
                    ++i;
                }
                ops.push_back(t);
            }
        }
        int opsSize = ops.size();

        Vector3D dp(opsSize, std::vector<std::vector<int>>(opsSize));
        return dfs(dp, 0, opsSize - 1, ops);
    }

private:
    static constexpr int ADD = -1;
    static constexpr int SUB = -2;
    static constexpr int MUL = -3;

    std::vector<int> dfs(Vector3D &dp, int left, int right, const std::vector<int> &ops)
    {
        if (dp[left][right].empty())
        {
            if (left == right)
            {
                dp[left][right].push_back(ops[left]);
            }
            else
            {
                for (int i = left; i < right; i += 2)
                {
                    auto leftRes = dfs(dp, left, i, ops);
                    auto rightRes = dfs(dp, i + 2, right, ops);
                    for (int &leftVal : leftRes)
                    {
                        for (int &rightVal : rightRes)
                        {
                            int res;
                            switch (ops[i + 1])
                            {
                                case ADD:
                                    res = leftVal + rightVal;
                                    break;
                                case SUB:
                                    res = leftVal - rightVal;
                                    break;
                                case MUL:
                                    res = leftVal * rightVal;
                                    break;
                            }
                            dp[left][right].push_back(res);
                        }
                    }
                }
            }
        }
        return dp[left][right];
    }
};

class Solution3
{
public:
    using Vector3D = std::vector<std::vector<std::vector<int>>>;

    std::vector<int> diffWaysToCompute(std::string expression)
    {
        int exprLen = expression.size();
        std::vector<int> ops;
        for (int i = 0; i < exprLen;)
        {
            if (expression[i] == '+')
            {
                ops.push_back(ADD);
                ++i;
            }
            else if (expression[i] == '-')
            {
                ops.push_back(SUB);
                ++i;
            }
            else if (expression[i] == '*')
            {
                ops.push_back(MUL);
                ++i;
            }
            else
            {
                int t = 0;
                while (i < exprLen && std::isdigit(expression[i]))
                {
                    t = t * 10 + (expression[i] - '0');
                    ++i;
                }
                ops.push_back(t);
            }
        }
        int opsSize = ops.size();

        // dp[l][r]={v1, v2, ...}，ops[l:r]按照不同优先级可能产生的结果
        Vector3D dp(opsSize, std::vector<std::vector<int>>(opsSize));
        for (int i = 0; i < opsSize; i += 2)
        {
            dp[i][i] = {ops[i]};
        }

        for (int i = 3; i <= opsSize; ++i)  // 枚举表达式长度
        {
            for (int j = 0; j + i <= opsSize; j += 2)   // 枚举left
            {
                int left = j;
                int right = j + i - 1;
                for (int k = j + 1; k < right; k += 2)  // 枚举操作符
                {
                    auto &leftRes = dp[left][k - 1];
                    auto &rightRes = dp[k + 1][right];
                    for (int &leftVal : leftRes)
                    {
                        for (int &rightVal : rightRes)
                        {
                            int res;
                            switch (ops[k])
                            {
                                case ADD:
                                    res = leftVal + rightVal;
                                    break;
                                case SUB:
                                    res = leftVal - rightVal;
                                    break;
                                case MUL:
                                    res = leftVal * rightVal;
                                    break;
                            }
                            dp[left][right].push_back(res);
                        }
                    }
                }
            }
        }

        return dp[0][opsSize - 1];
    }

private:
    static constexpr int ADD = -1;
    static constexpr int SUB = -2;
    static constexpr int MUL = -3;
};

int main()
{
    Solution3 solution;
    std::string expression = "2*3-4*5";
    std::vector<int> ans = solution.diffWaysToCompute(expression);
    debug::printVector(ans);
    return 0;
}

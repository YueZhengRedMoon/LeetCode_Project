#include <iostream>
#include <string>
#include <unordered_map>
#include "../debug/debug.h"

class Solution
{
public:
    std::string fractionToDecimal(int numerator, int denominator)
    {
        std::string ns = std::to_string(numerator);
        int a = ns[0] - '0', b = denominator, i = 1;
        bool isDecimal = false;

        const int MAX_ANS_LEN = 30;
        std::string ans;
        int r = -1;  // 分子除以分母得到的余数
        do
        {
            if (a >= b)
            {
                r = a % b;
                ans.push_back(a / b + '0');
                a = r * 10;
            }
            else    // a < b
            {
                if (isDecimal)
                {
                    ans.push_back('0');
                    a *= 10;
                }
                else
                {
                    if (i < ns.size())
                    {
                        a = a * 10 + (ns[i++] - '0');
                    }
                    else
                    {
                        if (ans.empty())
                        {
                            ans.push_back('0');
                        }
                        ans.push_back('.');
                        isDecimal = true;
                        a *= 10;
                    }
                }
            }
        } while (r != 0 && ans.size() < MAX_ANS_LEN);

        return ans;
    }
};

class Solution2
{
public:
    std::string fractionToDecimal(int numerator, int denominator)
    {
        long long a = numerator, b = denominator;
        std::string sign = a * b < 0 ? "-" : "";
        a = std::abs(a);
        b = std::abs(b);

        // 计算整数部分q和初始余数r
        long long q = a / b, r = a % b;
        if (r == 0) // 没有小数部分
        {
            return sign + std::to_string(q);
        }

        std::string ans = sign + std::to_string(q) + ".";
        std::unordered_map<long long, size_t> rToPos = {{r, ans.size()}};  // 记录初始余数对应的位置
        while (r)
        {
            // 计算小数点后的数字q，更新r
            r *= 10;
            q = r / b;
            r %= b;
            ans.push_back('0' + q);
            if (rToPos.find(r) != rToPos.end()) // 有循环节
            {
                size_t pos = rToPos[r];    // 循环节开始的位置
                return ans.substr(0, pos) + "(" + ans.substr(pos) + ")";
            }
            rToPos[r] = ans.size();
        }

        // 有限小数
        return ans;
    }
};

int main()
{
    Solution solution;
    logObj(solution.fractionToDecimal(1, 2));
    logObj(solution.fractionToDecimal(2, 1));
    logObj(solution.fractionToDecimal(4, 333));
    logObj(solution.fractionToDecimal(1, 3));
    logObj(solution.fractionToDecimal(5, 7));
    logObj(solution.fractionToDecimal(1, 12));
    logObj(solution.fractionToDecimal(13, 12));
    return 0;
}

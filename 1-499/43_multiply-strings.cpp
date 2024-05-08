#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    std::string multiply(std::string num1, std::string num2)
    {
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }

        if (num1.length() < num2.length())
        {
            std::swap(num1, num2);
        }

        int len1 = num1.size(), len2 = num2.size();
        std::string ans;
        for (int i = 0; i < len2; ++i)
        {
            std::string tmp;
            tmp.reserve(len1 + 2);
            int c = 0;  // 进位
            int b = num2[i] - '0';
            for (int j = len1 - 1; j >= 0; --j)
            {
                int a = num1[j] - '0';
                int res = a * b + c;
                tmp.push_back('0' + (res % 10));
                c = res / 10;
            }
            if (c > 0)
            {
                tmp.push_back('0' + c);
            }
            std::reverse(tmp.begin(), tmp.end());

            if (ans.empty())
            {
                std::swap(ans, tmp);
            }
            else
            {
                ans.push_back('0');
                add(ans, tmp);
            }
        }

        return ans;
    }

private:
    void add(std::string& num1, const std::string& num2)
    {
        int len1 = num1.size(), len2 = num2.size(); // len1 == len2 + 1
        int c = 0;  // 进位
        int res, i, j;
        for (i = len1 - 1, j = len2 - 1; j >= 0; --i, --j)
        {
            int a = num1[i] - '0', b = num2[j] - '0';
            res = a + b + c;
            num1[i] = '0' + res % 10;
            c = res / 10;
        }
        while (c > 0)
        {
            if (i >= 0)
            {
                if (num1[i] == '9')
                {
                    num1[i--] = '0';
                }
                else
                {
                    ++num1[i];
                    break;
                }
            }
            else
            {
                num1 = "1" + num1;
                break;
            }
        }
    }
};

class Solution2
{
public:
    std::string multiply(std::string num1, std::string num2)
    {
        if (num1 == "0" || num2 == "0")
            return "0";

        int len1 = num1.size(), len2 = num2.size();
        std::vector<int> ansArr(len1 + len2, 0);
        for (int i = len1 - 1; i >= 0; --i)
        {
            int a = num1[i] - '0';
            for (int j = len2 - 1; j >= 0; --j)
            {
                int b = num2[j] - '0';
                ansArr[i + j + 1] += a * b;
            }
        }

        for (int i = len1 + len2 - 1; i > 0; --i)
        {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }

        int i = ansArr[0] == 0 ? 1 : 0;
        std::string ans;
        ans.reserve(len1 + len2 - i);
        for (; i < len1 + len2; ++i)
        {
            ans.push_back('0' + ansArr[i]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

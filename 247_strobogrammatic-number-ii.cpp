#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::string> findStrobogrammatic(int n)
    {
        if (n == 1)
            ans.push_back("0");
        std::string num(n, '0');
        backtracking(num, 0, n - 1);
        return ans;
    }

private:
    std::vector<std::string> ans;

    void backtracking(std::string &num, int left, int right)
    {
        if (left > right)
        {
            ans.push_back(num);
            return;
        }

        if (left != 0)
        {
            num[left] = num[right] = '0';
            backtracking(num, left + 1, right - 1);
        }

        num[left] = num[right] = '1';
        backtracking(num, left + 1, right - 1);

        num[left] = num[right] = '8';
        backtracking(num, left + 1, right - 1);

        if (left < right)
        {
            num[left] = '6'; num[right] = '9';
            backtracking(num, left + 1, right - 1);

            num[left] = '9'; num[right] = '6';
            backtracking(num, left + 1, right - 1);
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
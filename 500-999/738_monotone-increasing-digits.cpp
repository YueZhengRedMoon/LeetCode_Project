#include <iostream>

class Solution
{
public:
    int monotoneIncreasingDigits(int n)
    {
        std::string s = std::to_string(n);
        int index = -1;
        for (int i = s.size() - 2; i >= 0; --i)
        {
            if (s[i] > s[i + 1])
            {
                --s[i];
                index = i + 1;
            }
        }
        if (index >= 0)
        {
            for (int i = index; i < s.size(); ++i)
            {
                s[i] = '9';
            }
        }
        return std::stoi(s);
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution solution;
    std::cout << solution.monotoneIncreasingDigits(n) << std::endl;
    return 0;
}
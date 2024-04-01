#include <iostream>
#include <algorithm>
#include <deque>

class Solution
{
public:
    std::string finalString(std::string s)
    {
        std::string ans;
        ans.reserve(s.size());
        for (char c : s)
        {
            if (c == 'i')
            {
                std::reverse(ans.begin(), ans.end());
            }
            else
            {
                ans.push_back(c);
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    std::string finalString(std::string s)
    {
        std::deque<char> deque;
        bool addToBack = true, printFrontToBack = true;
        for (char c : s)
        {
            if (c == 'i')
            {
                addToBack = !addToBack;
                printFrontToBack = !printFrontToBack;
            }
            else
            {
                if (addToBack)
                    deque.push_back(c);
                else
                    deque.push_front(c);
            }
        }
        if (printFrontToBack)
            return std::string(deque.begin(), deque.end());
        else
            return std::string(deque.rbegin(), deque.rend());
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

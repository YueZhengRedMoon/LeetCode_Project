#include <iostream>
#include <unordered_map>

class Solution
{
public:
    bool canPermutePalindrome(std::string s)
    {
        std::unordered_map<char, int> count;
        for (char c : s)
        {
            ++count[c];
        }
        bool hasOdd = false;
        for (auto it = count.begin(); it != count.end(); ++it)
        {
            if (it->second % 2 == 1)
            {
                if (hasOdd)
                    return false;
                hasOdd = true;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
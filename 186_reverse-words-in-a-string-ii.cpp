#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    void reverseWords(std::vector<char> &s)
    {
        std::reverse(s.begin(), s.end());
        int delta = 0;
        std::vector<char>::iterator blankIter;
        do
        {
            blankIter = std::find(s.begin() + delta, s.end(), ' ');
            std::reverse(s.begin() + delta, blankIter);
            delta = blankIter - s.begin() + 1;
        } while (blankIter != s.end());
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

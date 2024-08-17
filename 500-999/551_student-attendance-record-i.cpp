#include <iostream>
#include <vector>

class Solution
{
public:
    bool checkRecord(std::string s)
    {
        int cntA = 0, cntL = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == 'L')
            {
                if (++cntL >= 3)
                    return false;
            }
            else
            {
                cntL = 0;
            }
            if (s[i] == 'A')
            {
                if (++cntA >= 2)
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

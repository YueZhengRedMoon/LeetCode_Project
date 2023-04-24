#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::string predictPartyVictory(std::string senate)
    {
        std::vector<int> banned(senate.size(), false);
        int numR = std::count_if(senate.begin(), senate.end(), [](const char s) {return s == 'R';});
        int numD = senate.size() - numR;

        int i = 0, banR = 0, banD = 0;
        while (numR > 0 && numD > 0)
        {
            if (senate[i] == 'R')
            {
                if (!banned[i])
                {
                    if (banR > 0)
                    {
                        --banR;
                        banned[i] = true;
                        --numR;
                    }
                    else
                    {
                        ++banD;
                    }
                }
            }
            // senate[i] == 'D'
            else
            {
                if (!banned[i])
                {
                    if (banD > 0)
                    {
                        --banD;
                        banned[i] = true;
                        --numD;
                    }
                    else
                    {
                        ++banR;
                    }
                }
            }

            i = (i + 1) % senate.size();
        }

        if (numR > 0)
            return "Radiant";
        else
            return "Dire";
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
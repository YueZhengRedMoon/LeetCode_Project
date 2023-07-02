#include <iostream>
#include <vector>

class Solution
{
public:
    bool validWordSquare(std::vector<std::string> &words)
    {
        int n = words.size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < words[i].size(); ++j)
            {
                if (j >= words[i].size() && i < words[j].size())
                    return false;
                else if (i >= words[j].size() && j < words[i].size())
                    return false;
                else if (j >= words[i].size() && i >= words[j].size())
                    break;
                else if (words[i][j] != words[j][i])
                {
                    return false;
                }
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
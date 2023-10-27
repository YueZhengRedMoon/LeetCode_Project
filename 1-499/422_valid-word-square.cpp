#include <iostream>
#include <vector>

class Solution
{
public:
    bool validWordSquare(std::vector<std::string> &words)
    {
        int row = words.size();
        for (int i = 0; i < row; ++i)
        {
            int col = words[i].size();
            for (int j = 0; j < col; ++j)
            {
                if (j >= row || i >= words[j].size())
                    return false;
                if (words[i][j] != words[j][i])
                    return false;
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
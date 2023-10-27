#include <iostream>
#include <vector>

class Solution
{
public:
    bool judgeCircle(std::string moves)
    {
        int x = 0, y = 0;
        for (char op : moves)
        {
            switch (op)
            {
                case 'R':
                    ++x;
                    break;
                case 'L':
                    --x;
                    break;
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
            }
        }
        return x == 0 && y == 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

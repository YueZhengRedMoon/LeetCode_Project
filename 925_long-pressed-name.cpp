#include <iostream>
#include <vector>

class Solution
{
public:
    bool isLongPressedName(std::string name, std::string typed)
    {
        int j = 0;
        for (int i = 0; i < name.size(); ++i)
        {
            if (j >= typed.size())
            {
                return false;
            }

            if (name[i] != typed[j])
            {
                if (j == 0)
                {
                    return false;
                }

                while (typed[j - 1] == typed[j])
                {
                    ++j;
                    if (j == typed.size())
                    {
                        return false;
                    }
                }

                if (name[i] != typed[j])
                {
                    return false;
                }
            }
            ++j;
        }
        while (j < typed.size())
        {
            if (typed[j] != name.back())
            {
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
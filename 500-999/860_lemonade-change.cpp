#include <iostream>
#include <vector>

class Solution
{
public:
    bool lemonadeChange(std::vector<int> &bills)
    {
        int five = 0;
        int ten = 0;

        for (int bill : bills)
        {
            switch (bill)
            {
                case 5:
                    ++five;
                    break;
                case 10:
                    if (five > 0)
                    {
                        --five;
                        ++ten;
                    }
                    else
                    {
                        return false;
                    }
                    break;
                case 20:
                    if (five > 0 && ten > 0)
                    {
                        --five;
                        --ten;
                    }
                    else if (five > 2)
                    {
                        five -= 3;
                    }
                    else
                    {
                        return false;
                    }
                    break;
            }
        }
        return true;
    }
};

int main()
{

    return 0;
}
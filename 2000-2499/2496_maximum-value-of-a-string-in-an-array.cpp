#include <iostream>
#include <vector>

class Solution
{
public:
    int maximumValue(std::vector<std::string> &strs)
    {
        int maxVal = 0;
        for (std::string &str : strs)
        {
            int val = calcVal(str);
            if (val > maxVal)
                maxVal = val;
        }
        return maxVal;
    }

private:
    bool isNum(std::string &str)
    {
        for (char c : str)
        {
            if (isalpha(c))
            {
                return false;
            }
        }
        return true;
    }

    int calcVal(std::string &str)
    {
        if (isNum(str))
        {
            return std::stoi(str);
        }
        return str.size();
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
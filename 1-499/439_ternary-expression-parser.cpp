#include <iostream>
#include <vector>

class Solution
{
public:
    std::string parseTernary(std::string expression)
    {
        constexpr int MAX_N = 1e4;
        int n = expression.size();
        int opTop = -1, objTop = -1;
        std::vector<char> opStack(MAX_N), objStack(MAX_N);
        for (int i = n - 1; i >= 0; --i)
        {
            if (expression[i] == '?' || expression[i] == ':')
            {
                opStack[++opTop] = expression[i];
            }
            else
            {
                objStack[++objTop] = expression[i];
                while (opTop >= 1 && opStack[opTop] == '?')
                {
                    // obj1  ?  obj2  :  obj3
                    opTop -= 2;
                    char obj1 = objStack[objTop], obj2 = objStack[objTop - 1], obj3 = objStack[objTop - 2];
                    objTop -= 2;
                    if (obj1 == 'F' || obj1 == '0')
                    {
                        objStack[objTop] = obj3;
                    }
                    else
                    {
                        objStack[objTop] = obj2;
                    }
                }
            }
        }
        return {objStack[0]};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

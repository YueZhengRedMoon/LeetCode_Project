#include <iostream>
#include <vector>

class Solution
{
public:
    bool confusingNumber(int n)
    {
        const int rotate[] = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
        int num = n;
        int newNum = 0;
        while (n > 0)
        {
            int a = n % 10;
            if (rotate[a] == -1)
            {
                return false;
            }
            newNum = newNum * 10 + rotate[a];
            n /= 10;
        }
        return newNum != num;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
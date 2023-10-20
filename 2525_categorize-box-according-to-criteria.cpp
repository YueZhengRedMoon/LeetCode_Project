#include <iostream>
#include <vector>

class Solution
{
public:
    std::string categorizeBox(int length, int width, int height, int mass)
    {
        long long volume = (long long) length * width * height;
        long long e4 = 10000, e9 = 1000000000;

        bool isBulky = (length >= e4 || width >= e4 || height >= e4 || volume >= e9);
        bool isHeavy = (mass >= 100);

        if (isBulky && isHeavy)
            return "Both";
        else if (!isBulky && !isHeavy)
            return "Neither";
        else if (isBulky && !isHeavy)
            return "Bulky";
        else
            return "Heavy";
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

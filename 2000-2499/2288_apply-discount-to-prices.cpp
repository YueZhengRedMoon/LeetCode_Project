#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

class Solution
{
public:
    std::string discountPrices(std::string sentence, int discount)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        int n = sentence.size(), i = 0;
        double d = 1.0 - (discount / 100.0);
        while (i < n)
        {
            if (sentence[i] == '$' && (i == 0 || sentence[i - 1] == ' '))
            {
                int j = i + 1;
                long long price = 0;
                while (j < n)
                {
                    if (std::isdigit(sentence[j]))
                        price = price * 10 + (sentence[j++] - '0');
                    else
                        break;
                }
                if ((j == n || sentence[j] == ' ') && j > i + 1)
                {
                    oss << '$' << price * d;
                    i = j;
                    continue;
                }
            }
            oss << sentence[i++];
        }
        return oss.str();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

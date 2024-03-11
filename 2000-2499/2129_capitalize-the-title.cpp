#include <iostream>
#include <string>
#include <cctype>

class Solution
{
public:
    std::string capitalizeTitle(std::string title)
    {
        int n = title.size(), i, j;
        for (i = 0, j = 0; j < n; ++j)
        {
            if (title[j] == ' ')
            {
                if (j - i > 2)
                {
                    title[i] = std::toupper(title[i]);
                }
                i = j + 1;
            }
            else
            {
                title[j] = std::tolower(title[j]);
            }
        }
        if (j - i > 2)
        {
            title[i] = std::toupper(title[i]);
        }
        return title;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

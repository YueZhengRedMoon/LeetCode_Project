#include <iostream>
#include <string>

class Solution
{
public:
    int compareVersion(std::string version1, std::string version2)
    {
        int i = 0, j = 0, len1 = version1.size(), len2 = version2.size();
        while (i < len1 || j < len2)
        {
            int val1 = 0;
            while (i < len1 && version1[i] != '.')
            {
                val1 = val1 * 10 + (version1[i++] - '0');
            }
            ++i;

            int val2 = 0;
            while (j < len2 && version2[j] != '.')
            {
                val2 = val2 * 10 + (version2[j++] - '0');
            }
            ++j;

            if (val1 < val2)
                return -1;
            else if (val1 > val2)
                return 1;
        }
        return 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

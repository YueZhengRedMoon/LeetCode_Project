#include <iostream>
#include <vector>

class StringIterator
{
public:
    StringIterator(std::string compressedString)
    {
        int len = compressedString.size(), i = 0;
        while (i < len)
        {
            if (std::isdigit(compressedString[i]))
            {
                int count = 0;
                while (i < len && std::isdigit(compressedString[i]))
                {
                    count = count * 10 + (compressedString[i] - '0');
                    ++i;
                }
                str.back().second = count;
            }
            else
            {
                str.emplace_back(compressedString[i], 1);
                ++i;
            }
        }
        index = 0;
    }

    char next()
    {
        if (!hasNext())
            return ' ';

        char res = str[index].first;
        if (--str[index].second == 0)
        {
            ++index;
        }
        return res;
    }

    bool hasNext()
    {
        return index < str.size();
    }

private:
    std::vector<std::pair<char, int>> str;
    int index;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

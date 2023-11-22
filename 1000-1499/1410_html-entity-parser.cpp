#include <iostream>
#include <vector>
class Solution
{
public:
    std::string entityParser(std::string text)
    {
        std::size_t n = text.size();
        std::string ans;
        ans.reserve(n);
        int i  = 0;
        while (i < n)
        {
            if (text[i] != '&')
            {
                ans.push_back(text[i++]);
                continue;
            }

            // text[i] == '&'
            if (i + 5 < n && text[i + 1] == 'q' && text[i + 2] == 'u' && text[i + 3] == 'o' && text[i + 4] == 't' && text[i + 5] == ';')
            {
                i += 6;
                ans.push_back('\"');
            }
            else if (i + 5 < n && text[i + 1] == 'a' && text[i + 2] == 'p' && text[i + 3] == 'o' && text[i + 4] == 's' && text[i + 5] == ';')
            {
                i += 6;
                ans.push_back('\'');
            }
            else if (i + 4 < n && text[i + 1] == 'a' && text[i + 2] == 'm' && text[i + 3] == 'p' && text[i + 4] == ';')
            {
                i += 5;
                ans.push_back('&');
            }
            else if (i + 3 < n && text[i + 1] == 'g' && text[i + 2] == 't' && text[i + 3] == ';')
            {
                i += 4;
                ans.push_back('>');
            }
            else if (i + 3 < n && text[i + 1] == 'l' && text[i + 2] == 't' && text[i + 3] == ';')
            {
                i += 4;
                ans.push_back('<');
            }
            else if (i + 6 < n && text[i + 1] == 'f' && text[i + 2] == 'r' && text[i + 3] == 'a' && text[i + 4] == 's' && text[i + 5] == 'l' && text[i + 6] == ';')
            {
                i += 7;
                ans.push_back('/');
            }
            else
            {
                ans.push_back(text[i++]);
            }
        }
        ans.shrink_to_fit();
        return ans;
    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

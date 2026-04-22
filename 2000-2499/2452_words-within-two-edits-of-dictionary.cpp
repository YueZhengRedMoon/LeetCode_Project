#include <iostream>
#include <vector>
#include <string_view>

class Solution
{
public:
    std::vector<std::string> twoEditWords(std::vector<std::string>& queries, std::vector<std::string>& dictionary)
    {
        std::vector<std::string> ans;
        for (const std::string& q : queries)
        {
            for (std::string_view d : dictionary)
            {
                if (isWithin2Edits(q, d))
                {
                    ans.push_back(q);
                    break;
                }
            }
        }
        return ans;
    }

private:
    bool isWithin2Edits(std::string_view s1, std::string_view s2)
    {
        int edits = 0, n = s1.size();
        for (int i = 0; i < n && edits <= 2; ++i)
        {
            if (s1[i] != s2[i])
                ++edits;
        }
        return edits <= 2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
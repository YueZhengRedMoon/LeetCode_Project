#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int countWords(std::vector<std::string> &words1, std::vector<std::string> &words2)
    {
        std::unordered_map<std::string, int> counter1, counter2;
        for (const std::string &word : words1)
            ++counter1[word];
        for (const std::string &word : words2)
            ++counter2[word];

        int ans = 0;
        for (const std::string &word : words1)
        {
            if (counter1[word] == 1 && counter2.find(word) != counter2.end() && counter2[word] == 1)
                ++ans;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

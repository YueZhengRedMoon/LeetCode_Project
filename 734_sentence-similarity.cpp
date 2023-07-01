#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    bool areSentencesSimilar(std::vector<std::string> &sentence1,
                             std::vector<std::string> &sentence2,
                             std::vector<std::vector<std::string>> &similarPairs)
    {
        int size1 = sentence1.size(), size2 = sentence2.size();
        if (size1 != size2)
            return false;

        std::unordered_map<std::string, std::unordered_set<std::string>> similar;
        for (const std::vector<std::string> &pair : similarPairs)
        {
            similar[pair[0]].emplace(pair[1]);
            similar[pair[1]].emplace(pair[0]);
        }

        for (int i = 0; i < size1; ++i)
        {
            if (sentence1[i] != sentence2[i])
            {
                std::unordered_set<std::string> &set = similar[sentence1[i]];
                if (set.find(sentence2[i]) == set.end())
                {
                    return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
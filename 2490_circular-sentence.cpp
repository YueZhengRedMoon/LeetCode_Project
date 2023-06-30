#include <iostream>
#include <vector>
#include <sstream>

class Solution
{
public:
    bool isCircularSentence(std::string sentence)
    {
        std::istringstream iss(sentence);
        char tail = sentence.back();
        std::string word;
        while (iss >> word)
        {
            if (word[0] != tail)
                return false;

            tail = word.back();
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
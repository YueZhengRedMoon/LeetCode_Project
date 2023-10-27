#include <iostream>
#include <vector>

class Solution
{
public:
    bool haveConflict(std::vector<std::string> &event1, std::vector<std::string> &event2)
    {
        int event1Start = 60 * (std::stoi(event1[0].substr(0, 2)))
                            + (std::stoi(event1[0].substr(3, 2)));
        int event1End = 60 * (std::stoi(event1[1].substr(0, 2)))
                          + (std::stoi(event1[1].substr(3, 2)));
        int event2Start = 60 * (std::stoi(event2[0].substr(0, 2)))
                          + (std::stoi(event2[0].substr(3, 2)));
        int event2End = 60 * (std::stoi(event2[1].substr(0, 2)))
                        + (std::stoi(event2[1].substr(3, 2)));

        if (event1Start < event2Start)
        {
            return event1End >= event2Start;
        }
        else if (event1Start > event2Start)
        {
            return event2End >= event1Start;
        }
        else
        {
            return true;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
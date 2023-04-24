#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    using People = std::pair<std::string*, int>;

    std::vector<std::string> sortPeople(std::vector<std::string> &names, std::vector<int> &heights)
    {
        std::vector<People> people(names.size());
        for (int i = 0; i < names.size(); ++i)
        {
            people[i].first = &names[i];
            people[i].second = heights[i];
        }

        std::sort(people.begin(), people.end(), greater);

        std::vector<std::string> result;
        result.reserve(names.size());
        std::transform(people.begin(), people.end(), std::back_inserter(result),
                       [](const People &person) {return *(person.first);});
        return result;
    }

private:
    static bool greater(const People &lhs, const People &rhs)
    {
        return lhs.second > rhs.second;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
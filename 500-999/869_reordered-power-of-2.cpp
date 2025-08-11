#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

std::string intToSortedStr(int n)
{
    std::string s = std::to_string(n);
    std::sort(s.begin(), s.end());
    return s;
}

std::unordered_set<std::string> pow2SortedStr;

int init = []() {
    const int MAX_N = 1'000'000'000;
    for (int i = 1; i < MAX_N; i <<= 1)
    {
        pow2SortedStr.insert(intToSortedStr(i));
    }
    return 0;
}();

class Solution
{
public:
    bool reorderedPowerOf2(int n)
    {
        std::string s = intToSortedStr(n);
        return pow2SortedStr.find(s) != pow2SortedStr.end();
    }
};

class Solution2
{
public:
    bool reorderedPowerOf2(int n)
    {
        std::string s = std::to_string(n);
        std::sort(s.begin(), s.end());
        do
        {
            if (s[0] == '0')
                continue;

            int x = std::stoi(s);
            if ((x & (x - 1)) == 0)
                return true;
        } while (std::next_permutation(s.begin(), s.end()));
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

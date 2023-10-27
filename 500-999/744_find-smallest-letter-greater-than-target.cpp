#include <iostream>
#include <vector>

class Solution
{
public:
    char nextGreatestLetter(std::vector<char> &letters, char target)
    {
        int n = letters.size();
        int left = 0, right = n;
        char ans = letters[0];
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (letters[mid] > target)
            {
                ans = letters[mid];
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

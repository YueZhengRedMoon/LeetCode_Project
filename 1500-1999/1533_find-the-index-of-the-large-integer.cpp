#include <iostream>
#include <vector>

class ArrayReader
{
public:
    // Compares the sum of arr[l..r] with the sum of arr[x..y]
    // return 1 if sum(arr[l..r]) > sum(arr[x..y])
    // return 0 if sum(arr[l..r]) == sum(arr[x..y])
    // return -1 if sum(arr[l..r]) < sum(arr[x..y])
    int compareSub(int l, int r, int x, int y);

    // Returns the length of the array
    int length();
};

class Solution
{
public:
    int getIndex(ArrayReader &reader)
    {
        int len = reader.length();
        int left = 0, right = len - 1;
        while (left < right)
        {
            int mid = (right + left) >> 1;
            int res;
            if ((right - left + 1) % 2 == 0)
            {
                res = reader.compareSub(left, mid, mid + 1, right);
                if (res == 1)
                    right = mid;
                else
                    left = mid + 1;
            }
            else
            {
                res = reader.compareSub(left, mid, mid, right);
                if (res == 1)
                    right = mid - 1;
                else if (res == -1)
                    left = mid + 1;
                else
                    return mid;
            }
        }
        return left;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

class Solution
{
public:
    int getWinner(std::vector<int>& arr, int k)
    {
        int n = arr.size();
        if (k >= n)
        {
            return *std::max_element(arr.begin(), arr.end());
        }

        std::vector<int> nextLarge(n, 2 * n);
        std::stack<int> stack;
        for (int i = 2 * n - 1; i >= n; --i)
        {
            while (!stack.empty() && arr[i % n] > arr[stack.top() % n])
            {
                stack.pop();
            }
            stack.push(i);
        }
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stack.empty() && arr[i] >= arr[stack.top() % n])
            {
                stack.pop();
            }
            if (!stack.empty())
            {
                nextLarge[i] = stack.top();
            }
            stack.push(i);
        }

        if (nextLarge[0] >= k + 1)
            return arr[0];

        int max = arr[0];
        for (int i = 1; i < n; ++i)
        {
            if (arr[i] > max)
            {
                max = arr[i];
                if (nextLarge[i] - i >= k)
                {
                    return arr[i];
                }
            }
        }

        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

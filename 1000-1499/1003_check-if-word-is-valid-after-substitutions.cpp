#include <iostream>
#include <vector>

class Solution
{
public:
    bool isValid(std::string s)
    {
        std::vector<int> stack(s.size());
        int top = -1;
        for (char c : s)
        {
            if (top < 0)
            {
                if (c == 'a')
                {
                    stack[++top] = 'a';
                }
                else
                {
                    return false;
                }
            }
            else
            {
                switch (c)
                {
                    case 'a':
                        stack[++top] = 'a';
                        break;
                    case 'b':
                        if (stack[top] == 'a')
                        {
                            stack[++top] = 'b';
                        }
                        else
                        {
                            return false;
                        }
                        break;
                    case 'c':
                        if (top < 1 || stack[top] != 'b')
                        {
                            return false;
                        }
                        else
                        {
                            top -= 2;
                        }
                        break;
                }
            }
        }

        return top == -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
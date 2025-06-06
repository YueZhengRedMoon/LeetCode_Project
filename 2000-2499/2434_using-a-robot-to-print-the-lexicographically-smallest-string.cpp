#include <iostream>
#include <stack>
#include <string>
#include <vector>

// 如果栈顶 <= 剩余字母（后缀s[i+1:]中的最小值，就立刻出栈
class Solution
{
public:
    std::string robotWithString(std::string s)
    {
        int n = s.size();

        // 计算后缀最小值
        std::vector<char> sufMin(n + 1);
        sufMin[n] = 'z';
        for (int i = n - 1; i >= 0; --i)
        {
            sufMin[i] = std::min(sufMin[i + 1], s[i]);
        }

        std::string ans;
        ans.reserve(n);
        std::stack<char> st;
        for (int i = 0; i < n; ++i)
        {
            st.push(s[i]);
            while (!st.empty() && st.top() <= sufMin[i + 1])
            {
                ans.push_back(st.top());
                st.pop();
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

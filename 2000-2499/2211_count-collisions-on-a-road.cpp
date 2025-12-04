#include <iostream>
#include <string>
#include <stack>

class Solution
{
public:
    int countCollisions(std::string directions)
    {
        std::stack<char> st;
        int ans = 0;
        for (char d : directions)
        {
            while (!st.empty())
            {
                char preDir = st.top();
                if (preDir == 'R')
                {
                    if (d == 'L')   // RL碰撞
                    {
                        ans += 2;
                        d = 'S';    // 两车碰撞后，等价于变为一辆停着的车
                        st.pop();
                    }
                    else if (d == 'S')  // RS碰撞
                    {
                        ++ans;
                        st.pop();
                    }
                    else    // d == 'R', RR不发生碰撞
                    {
                        break;
                    }
                }
                else if (preDir == 'S')
                {
                    if (d == 'L')   // SL碰撞
                    {
                        ++ans;
                        d = 'S';    // 两车碰撞后，等价于变为一辆停着的车
                        st.pop();
                    }
                    // d == 'R' or 'S'，当前以及剩下右边的车不可能与前面左边的车发生碰撞了
                    else
                    {
                        clearStack(st);
                    }
                }
                else    // preDir == 'L'，当前以及剩下右边的车不可能与前面左边的车发生碰撞了
                {
                    clearStack(st);
                }
            }
            st.push(d);
        }
        return ans;
    }

private:
    void clearStack(std::stack<char>& st)
    {
        std::stack<char> empty;
        std::swap(empty, st);
    }
};

class Solution2
{
public:
    int countCollisions(std::string directions)
    {
        int n = directions.size();

        // 前缀向左的车不会发生碰撞
        int l = 0;
        while (l < n && directions[l] == 'L')
            ++l;

        // 后缀向右的车不会发生碰撞
        int r = n;
        while (r > l && directions[r - 1] == 'R')
            --r;

        // 剩下非静止的车必然会碰撞
        int ans = 0;
        for (int i = l; i < r; ++i)
        {
            if (directions[i] != 'S')
                ++ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
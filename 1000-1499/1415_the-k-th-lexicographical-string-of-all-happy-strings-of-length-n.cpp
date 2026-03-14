#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int MAX_N = 11;
std::vector<std::string> happyStr[MAX_N];

void dfs(std::string s, int i)
{
    if (i >= MAX_N)
    {
        return;
    }

    happyStr[i++].push_back(s);
    char back = s.back();
    if (back == 'a')
    {
        dfs(s + "b", i);
        dfs(s + "c", i);
    }
    else if (back == 'b')
    {
        dfs(s + "a", i);
        dfs(s + "c", i);
    }
    else    // back == 'c'
    {
        dfs(s + "a", i);
        dfs(s + "b", i);
    }
}

int init = []() {
    dfs("a", 1);
    dfs("b", 1);
    dfs("c", 1);

//    for (int i = 1; i < MAX_N; ++i)
//    {
//        std::sort(happyStr[i].begin(), happyStr[i].end());
//    }
    return 0;
}();

class Solution
{
public:
    std::string getHappyString(int n, int k)
    {
        if (k > happyStr[n].size())
        {
            return "";
        }
        else
        {
            return happyStr[n][k - 1];
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
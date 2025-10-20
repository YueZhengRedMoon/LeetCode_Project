#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    std::string findLexSmallestString(std::string s, int a, int b)
    {
        int n = s.size();
        std::vector<int> vis(n);    // 每个位置是否被轮转过
        std::string ans = s;
        s = s + s;  // 将s延长一倍，方便截距轮转后的字符串t
        for (int i = 0; vis[i] == 0; i = (i + b) % n)
        {
            vis[i] = 1;
            for (int j = 0; j < 10; ++j)    // 枚举奇数位的累加次数，最多累加10次
            {
                // 枚举偶数位的累加次数k
                // 如果b为偶数，则不会对偶数位进行累加
                int kLimit = b % 2 == 0 ? 0 : 9;
                for (int k = 0; k <= kLimit; ++k)
                {
                    std::string t = s.substr(i, n); // 每次进行累加之前，重新截取 t

                    // 奇数位累加
                    for (int p = 1; p < n; p += 2)
                    {
                        t[p] = '0' + (t[p] - '0' + j * a) % 10;
                    }

                    // 偶数位累加
                    for (int p = 0; p < n; p += 2)
                    {
                        t[p] = '0' + (t[p] - '0' + k * a) % 10;
                    }
                    ans = std::min(ans, t);
                }
            }
        }
        return ans;
    }
};

//  错误
class Solution2
{
public:
    std::string findLexSmallestString(std::string s, int a, int b)
    {
        std::unordered_set<std::string> addSet; // 通过累加操作可以得到的字符串集合
        bool isRepeated = false;                // 是否生成了重复字符串
        int n = s.size();
        std::string newS = s;
        while (!isRepeated)
        {
            for (int i = 1; i < n; i += 2)
            {
                newS[i] = add(newS[i], a);
            }
            isRepeated = !addSet.insert(newS).second;
        }

        std::string ans = s;
        // 轮转
        int delta = b % 2 ? 1 : 2;
        for (auto it = addSet.begin(); it != addSet.end(); ++it)
        {
            std::string t = *it;
            ans = std::min(ans, t);
            for (int i = 1; i < n; i += delta)
            {
                rightShift(t, delta);
                ans = std::min(ans, t);

                if (delta == 1)
                {
                    std::string newT = t;
                    isRepeated = addSet.find(newT) == addSet.end();
                    while (!isRepeated)
                    {
                        for (int j = 1; j < n; j += 2)
                        {
                            newT[j] = add(newT[j], a);
                        }
                        isRepeated = !addSet.insert(newT).second;

                        if (!isRepeated)
                        {
                            ans = std::min(ans, newT);
                        }
                    }
                }
            }
        }

        return ans;
    }

private:
    char add(char c, int a)
    {
        return ((c - '0' + a) % 10) + '0';
    }

    // 将字符串s右移x位，x = 1 or 2
    void rightShift(std::string& s, int x)
    {
        int n = s.size();   // n是偶数且n>=2
        if (x == 1)
        {
            char t = s[n - 1];
            for (int i = n - 1; i > 0; --i)
            {
                s[i] = s[i - 1];
            }
            s[0] = t;
        }
        else    // x == 2
        {
            char t1 = s[n - 1], t0 = s[n - 2];
            for (int i = n - 1; i >= 2; --i)
            {
                s[i] = s[i - 2];
            }
            s[0] = t0;
            s[1] = t1;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
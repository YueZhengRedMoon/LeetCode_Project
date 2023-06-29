#include <iostream>
#include <vector>

class Solution
{
public:
    bool isOneEditDistance(std::string s, std::string t)
    {
        // 在两个字符串末尾都加上一个相同的字符，以方便处理空串
        s.push_back('t');
        t.push_back('t');

        int sLen = s.size(), tLen = t.size();
        if (std::abs(sLen - tLen) > 1)
            return false;

        // 为了方便处理，确保sLen >= tLen
        if (sLen < tLen)
        {
            std::swap(s, t);
            std::swap(sLen, tLen);
        }

        bool isEdited = false;
        for (int i = 0, j = 0; i < tLen && j < sLen; ++i, ++j)
        {
            if (t[i] != s[j])
            {
                // 已经编辑过了一次，又出现了不同的字符
                if (isEdited)
                    return false;

                isEdited = true;
                if (tLen < sLen)    // t的长度小于s的长度，编辑的方法只能是在t中插入s[i]
                {
                    --i;    // 比较t[i]与s[j+1]
                }
                // else: t的长度等于s的长度，编辑的方法只能是修改
            }
        }

        return isEdited;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

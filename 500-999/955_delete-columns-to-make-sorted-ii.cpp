#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int minDeletionSize(std::vector<std::string>& strs)
    {
        int n = strs.size(), m = strs[0].size();
        std::vector<std::string> a(n);  // 最终得到的字符串数组
        int ans = 0;
        for (int j = 0; j < m; ++j)
        {
            bool del = false;
            for (int i = 0; i < n - 1; ++i)
            {
                if (a[i] + strs[i][j] > a[i + 1] + strs[i + 1][j])
                {
                    // j列不是升序，必须删
                    ++ans;
                    del = true;
                    break;
                }
            }
            if (!del)
            {
                // j列是升序，不删更好
                for (int i = 0; i < n; ++i)
                {
                    a[i] += strs[i][j];
                }
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int minDeletionSize(std::vector<std::string>& strs)
    {
        int n = strs.size(), m = strs[0].size();
        std::vector<int> checkList(n - 1);
        std::iota(checkList.begin(), checkList.end(), 0);

        int ans = 0;
        for (int j = 0; j < m; ++j)
        {
            bool del = false;
            for (int i : checkList)
            {
                if (strs[i][j] > strs[i + 1][j])    // j列不是升序，必须删
                {
                    ++ans;
                    del = true;
                    break;
                }
            }

            if (del)
                continue;

            // j列是升序，不删更好
            int newSize = 0;
            for (int i : checkList)
            {
                if (strs[i][j] == strs[i + 1][j])
                {
                    // 相邻字母相等，下一列 i 和 i+1 需要继续比大小
                    checkList[newSize++] = i;   // 原地覆盖
                }
            }
            checkList.resize(newSize);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
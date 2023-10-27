#include <iostream>
#include <algorithm>
#include <vector>

class ArrayReader
{
public:
    // Compares 4 different elements in the array
    // return 4 if the values of the 4 elements are the same (0 or 1).
    // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
    // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
    int query(int a, int b, int c, int d);

    // Returns the length of the array
    int length();
};

class Solution
{
public:
    int guessMajority(ArrayReader &reader)
    {
        int len = reader.length();
        int equalCnt = 0, notEqualCnt = 0, notEqualIdx = 0;
        int abcd[4];
        for (int i = 1; i < len; ++i)
        {
            for (int j = 1, k = 1; j < len && k < 4; ++j)
            {
                if (j != i)
                {
                    abcd[k++] = j;
                }
            }
            int res1 = reader.query(0, abcd[1], abcd[2], abcd[3]);
            abcd[0] = i;
            std::sort(std::begin(abcd), std::end(abcd));
            int res2 = reader.query(abcd[0], abcd[1], abcd[2], abcd[3]);
            if (res1 == res2)
            {
                ++equalCnt;
            }
            else
            {
                ++notEqualCnt;
                notEqualIdx = i;
            }
        }

        if (equalCnt >= notEqualCnt)
        {
            return 0;
        }
        else if (equalCnt + 1 == notEqualCnt)
        {
            return -1;
        }
        else
        {
            return notEqualIdx;
        }
    }
};

class Solution2
{
public:
    int guessMajority(ArrayReader &reader)
    {
        int n = reader.length();
        std::vector<int> v(n);
        v[0] = 1;

        auto find = [&](int num) {
            int idx = -1;
            for (int i = 0; i < n; ++i)
            {
                if (v[i] == num)
                {
                    idx = i;
                    break;
                }
            }
            return idx;
        };

        int q0123 = reader.query(0, 1, 2, 3);
        int q0124 = reader.query(0, 1, 2, 4);
        int q0134 = reader.query(0, 1, 3, 4);
        int q0234 = reader.query(0, 2, 3, 4);
        int q1234 = reader.query(1, 2, 3, 4);
        v[1] = (q0234 == q1234);
        v[2] = (q0134 == q1234);
        v[3] = (q0124 == q1234);
        v[4] = (q0123 == q1234);

        int sum = v[0] + v[1] + v[2] + v[3] + v[4];
        int prev = q1234;
        for (int i = 5; i < n; ++i)
        {
            // prev = reader.query(i - 4, i - 3, i - 2, i - 1);
            int cur = reader.query(i - 3, i - 2, i - 1, i);
            if (prev == cur)
            {
                v[i] = v[i - 4];
            }
            else
            {
                v[i] = 1 - v[i - 4];
            }
            prev = cur;
            sum += v[i];
        }

        if (sum * 2 == n)
        {
            return -1;
        }
        if (sum * 2 < n)
        {
            return find(0);
        }
        else
        {
            return find(1);
        }
    }
};

class Solution3
{
public:
    int guessMajority(ArrayReader &reader)
    {
        // 假设nums[0] = 0
        int cnt0 = 1, cnt1 = 0;
        int q0234 = reader.query(0, 2, 3, 4);
        int q1234 = reader.query(1, 2, 3, 4);
        // 从start开始每两个数一查
        int start, p, q;
        // 记录任意一个0/1的位置
        int where0 = -1, where1 = -1;
        if (q0234 == q1234)
        {
            // nums[1] = 0;
            ++cnt0;
            start = 2;
            p = 0;
            q = 1;
            where0 = 0;
        }
        else
        {
            // nums[1] = 1
            ++cnt1;
            int q0134 = reader.query(0, 1, 3, 4);
            if (q0134 == q1234)
            {
                // nums[2] = 0
                ++cnt0;
                start = 3;
                p = 0;
                q = 2;
                where0 = 0;
                where1 = 1;
            }
            else
            {
                // nums[2] = 1， 为了方便后续编码可以交换一下
                // 即nums[0] = 1, nums[1] = nums[2] = 0
                cnt0 = 2;
                cnt1 = 1;
                start = 3;
                p = 1;
                q = 2;
                where0 = 1;
                where1 = 0;
            }
        }

        // nums[p] == nums[q] == 0
        // 目前为止，0 的个数多于 1 的个数，如果在接下来的查找中没有出现两个 1 的情况（即返回值为 0），那么 1 的个数一定小于等于 0
        // 因此在出现了两个 1 的时候再记录 1 的位置也不迟
        int n = reader.length(), i, cur;
        for (i = start; i + 1 < n; i += 2)
        {
            cur = reader.query(p, q, i, i + 1);
            if (cur == 0)
            {
                cnt1 += 2;
                if (where1 == -1)
                    where1 = i;
            }
            else if (cur == 2)
            {
                ++cnt0;
                ++cnt1;
            }
            else
            {
                cnt0 += 2;
            }
        }

        if (i != n)
        {
            int q0123 = reader.query(0, 1, 2, 3);
            int extra = reader.query(1, 2, 3, n - 1);
            int status = (q0123 == extra) ^ (p == 0);
            if (status == 0)
            {
                ++cnt0;
            }
            else
            {
                ++cnt1;
            }
        }

        if (cnt0 == cnt1)
        {
            return -1;
        }

        return cnt0 < cnt1 ? where1 : where0;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
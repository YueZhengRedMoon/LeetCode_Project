#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int integerReplacement(int n)
    {
        return backtracking(n);
    }

private:
    std::unordered_map<long long, int> memo;

    int backtracking(long long n)
    {
        if (memo.find(n) == memo.end())
        {
            int count = 0;
            long long temp = n;
            while (temp != 1)
            {
                if (temp % 2 == 0)
                {
                    temp /= 2;
                    ++count;
                }
                else
                {
                    count += std::min(backtracking(temp + 1), backtracking(temp - 1)) + 1;
                    break;
                }
            }
            return memo[n] = count;
        }
        return memo[n];
    }
};

/** 贪心的思路，对于一个数n来说，进行除以2的操作是下降的最快的
 *  当n为奇数时，它的二进制最低2位可能是11或01，即分别表示n%4=3和n%4=1,
 *  如果n的二进制最低两位是11，即此时n%4=3，应该将其加1，使二进制位最低两位变为00，这样n就可以连除两次，
 *  同理，如果n的二进制最低两位是01，即此时n%4=1，应该将其减一，使二进制位最低两位变为00，这样n也可以连除两次，
 *  否则的话，二进制位最低两位变为10，此时除以一次2后n又变成奇数，又要进行加一或减一，下降的速度就变慢了 */
class Solution2
{
public:
    int integerReplacement(int n)
    {
        int ans = 0;
        while (n != 1)
        {
            if (n % 2 == 0)
            {
                ++ans;
                n /= 2;
            }
            else if (n % 4 == 1)
            {
                ans += 2;
                n /= 2; // 等价于(n - 1) / 2
            }
            else
            {
                if (n == 3)
                {
                    ans += 2;
                    n = 1;
                }
                else
                {
                    ans += 2;
                    n = n / 2 + 1;  // 等价于 (n + 1) / 2
                }
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
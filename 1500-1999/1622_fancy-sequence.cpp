#include <iostream>
#include <vector>

class Fancy
{
public:
    Fancy() : add(0), mul(1) {}

    void append(int val)
    {
        // 注意这里有减法，计算结果可能是负数，+MOD 可以保证计算结果非负
        vals.push_back((val - add + MOD) * pow(mul, MOD - 2) % MOD);
    }

    void addAll(int inc)
    {
        add = (add + inc) % MOD;
    }

    void multAll(int m)
    {
        mul = mul * m % MOD;
        add = add * m % MOD;
    }

    int getIndex(int idx)
    {
        if (idx >= vals.size())
        {
            return -1;
        }
        return (vals[idx] * mul + add) % MOD;
    }

private:
    static constexpr int MOD = 1'000'000'007;
    std::vector<int> vals;
    long long add;
    long long mul;

    // 计算x^n % MOD
    long long pow(long long x, int n)
    {
        long long res = 1;
        while (n)
        {
            if (n % 2)
            {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n /= 2;
        }
        return res;
    }
};
int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
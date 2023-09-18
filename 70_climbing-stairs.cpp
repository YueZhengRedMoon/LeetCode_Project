#include <iostream>
#include <vector>

class Solution
{
public:
    /**
     * f[i] = 1 * f[i-1] + 1 * f[i-2]
     * f[i - 1] = 1 * f[i - 1] + 0 * f[i-2]
     * 则上式可以转换为矩阵乘法:
     * | f[i]   | = | 1 1 | . | f[i-1] | = ... = | 1 1 | ^(i - 1)  . | f[1] |
     * | f[i-1] |   | 1 0 |   | f[i-2] |         | 1 0 |             | f[0] |
     * */

    using Matrix = std::vector<std::vector<long long>>;

    int climbStairs(int n)
    {
        if (n <= 2)
            return n;

        Matrix m = {{1, 1}, {1, 0}};
        m = pow(m, n - 1);
        return (int) (m[0][0] + m[0][1]);
    }

private:
    Matrix multiply(const Matrix &a, const Matrix &b)
    {
        Matrix c(2, std::vector<long long>(2));
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }

    Matrix pow(Matrix a, int n)
    {
        Matrix res = {{1, 0}, {0, 1}};
        while (n)
        {
            if (n & 1)
                res = multiply(res, a);
            a = multiply(a, a);
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

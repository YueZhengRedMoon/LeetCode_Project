#include <iostream>
#include <vector>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n, q;
        std::cin >> n >> q;
        std::vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i];
        }

        for (int i = 0; i < q; ++i)
        {
            int x;
            std::cin >> x;

            int ans = 0;
            // 遍历二进制集合x的所有非空子集
            for (unsigned int sub = x; sub; sub = (sub - 1) & x)
            {
                if (sub <= n)
                {
                    ans += a[sub];
                }
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}

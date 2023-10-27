#include <iostream>
#include <vector>

class BookMyShow
{
public:
    BookMyShow(int n, int m)
    : sum(4 * n, 0)
    , min(4 * n, 0)
    {
        this->n = n;
        this->m = m;
    }

    std::vector<int> gather(int k, int maxRow)
    {
        int i = index(1, 1, n, maxRow + 1, m - k);
        if (i == 0)
            return {};
        long long seats = querySum(1, 1, n, i, i);
        add(1, 1, n, i, k);
        return {i - 1, static_cast<int>(seats)};
    }

    bool scatter(int k, int maxRow)
    {
        long long leftSeats = static_cast<long long>((maxRow + 1)) * m - querySum(1, 1, n, 1, maxRow + 1);
        if (leftSeats < k)
            return false;

        int i = index(1, 1, n, maxRow + 1, m - 1);
        while (true)
        {
            leftSeats = m - querySum(1, 1, n, i, i);
            if (k <= leftSeats)
            {
                add(1, 1, n, i, k);
                return true;
            }
            k -= leftSeats;
            add(1, 1, n, i, leftSeats);
            ++i;
        }
    }

private:
    std::vector<long long> sum;
    std::vector<int> min;
    int n, m;

    void add(int o, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            sum[o] += val;
            min[o] += val;
            return;
        }

        int mid = (l + r) / 2;
        if (idx <= mid)
        {
            add(o * 2, l, mid, idx, val);
        }
        else
        {
            add(o * 2 + 1, mid + 1, r, idx, val);
        }
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
        min[o] = std::min(min[o * 2], min[o * 2 + 1]);
    }

    long long querySum(int o, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return sum[o];
        }

        long long res = 0;
        int mid = (l + r) / 2;
        if (ql <= mid)
        {
            res += querySum(o * 2, l, mid, ql, qr);
        }
        if (qr > mid)
        {
            res += querySum(o * 2 + 1, mid + 1, r, ql, qr);
        }
        return res;
    }

    // 返回[1, R]范围内<=val的最小下标，如果不存在，返回0
    int index(int o, int l, int r, int qr, int val)
    {
        if (min[o] > val)
            return 0;
        if (l == r)
            return l;

        int mid = (l + r) / 2;
        if (min[o * 2] <= val)
            return index(o * 2, l, mid, qr, val);
        if (mid < qr)
            return index(o * 2 + 1, mid + 1, r, qr, val);
        return 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

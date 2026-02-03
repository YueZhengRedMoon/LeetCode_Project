#include <iostream>
#include <vector>

class Solution
{
public:
    long long minimumCost(std::string source, std::string target,
                          std::vector<char>& original, std::vector<char>& changed, std::vector<int>& cost)
    {
        const int MAX_ALPHA = 26;
        int costMat[MAX_ALPHA][MAX_ALPHA]{};    // costMat[x][y]=0表示无法将x转换成y
        int n = source.size(), m = original.size();
        for (int i = 0; i < m; ++i)
        {
            int x = index(original[i]), y = index(changed[i]);
            if (costMat[x][y] == 0 || costMat[x][y] > cost[i])
            {
                costMat[x][y] = cost[i];
            }
        }

        for (int k = 0; k < MAX_ALPHA; ++k)
        {
            for (int i = 0; i < MAX_ALPHA; ++i)
            {
                for (int j = 0; j < MAX_ALPHA; ++j)
                {
                    if (costMat[i][k] != 0 && costMat[k][j] != 0 && (costMat[i][k] + costMat[k][j] < costMat[i][j] || costMat[i][j] == 0))
                    {
                        costMat[i][j] = costMat[i][k] + costMat[k][j];
                    }
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int x = index(source[i]), y = index(target[i]);
            if (x != y)
            {
                if (costMat[x][y] == 0)
                {
                    return -1;
                }
                ans += costMat[x][y];
            }
        }
        return ans;
    }

private:
    int index(char c)
    {
        return c - 'a';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
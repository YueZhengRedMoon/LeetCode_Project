#include <iostream>
#include <vector>
#include <bitset>

class Solution
{
public:
    std::vector<int> findThePrefixCommonArray(std::vector<int>& A, std::vector<int>& B)
    {
        constexpr int MAX_N = 51;
        int n = A.size();
        std::bitset<MAX_N> setA, setB;
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            setA.set(A[i]);
            setB.set(B[i]);
            ans[i] = (setA & setB).count();
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
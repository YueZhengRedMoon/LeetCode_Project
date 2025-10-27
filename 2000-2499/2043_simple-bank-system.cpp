#include <iostream>
#include <vector>

class Bank
{
public:
    Bank(std::vector<long long>& inputBalance)
    : n(inputBalance.size())
    , balance(inputBalance)
    {

    }

    bool transfer(int account1, int account2, long long money)
    {
        if (account1 > n || account2 > n)
            return false;

        int id1 = account1 - 1, id2 = account2 - 1;

        if (balance[id1] < money)
            return false;

        balance[id1] -= money;
        balance[id2] += money;
        return true;
    }

    bool deposit(int account, long long money)
    {
        if (account  > n)
            return false;

        balance[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money)
    {
        if (account > n || balance[account - 1] < money)
            return false;

        balance[account - 1] -= money;
        return true;
    }

private:
    int n;
    std::vector<long long> balance;
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
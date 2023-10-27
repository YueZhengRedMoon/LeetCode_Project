#include <iostream>
#include <stack>

class StockSpanner
{
public:
    struct Stock
    {
        int price;
        int span;
    };

    StockSpanner()
    {

    }

    int next(int price)
    {
        int span = 1;
        while (!stack.empty() && stack.top().price <= price)
        {
            span += stack.top().span;
            stack.pop();
        }
        stack.push({price, span});
        return span;
    }

private:
    std::stack<Stock> stack;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <deque>

class MovingAverage
{
public:
    MovingAverage(int size) : sum(0), maxSize(size) {}

    double next(int val)
    {
        if (window.size() == maxSize)
        {
            sum -= window.front();
            window.pop_front();
        }
        window.push_back(val);
        sum += val;
        return sum / window.size();
    }

private:
    double sum;
    int maxSize;
    std::deque<int> window;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <deque>

class SnakeGame
{
public:
    SnakeGame(int width, int height, std::vector<std::vector<int>> &foodList) :
    w(width),
    h(height),
    food(foodList)
    {
        snake.emplace_back(0, 0);
        body.emplace(hash(0, 0));
    }

    int move(std::string direction)
    {
        int x = snake.front().first, y = snake.front().second;
        if (direction[0] == 'R')
            ++y;
        else if (direction[0] == 'D')
            ++x;
        else if (direction[0] == 'L')
            --y;
        else
            --x;

        int tailX = snake.back().first, tailY = snake.back().second;
        if (x < 0 || x >= h || y < 0 || y >= w || (!(x == tailX && y == tailY) && body.find(hash(x, y)) != body.end()))
            return -1;

        if (i < food.size() && x == food[i][0] && y == food[i][1])
        {
            snake.emplace_front(x, y);
            body.emplace(hash(x, y));
            ++i;
            return ++score;
        }


        snake.pop_back();
        snake.emplace_front(x, y);
        body.erase(hash(tailX, tailY));
        body.emplace(hash(x, y));
        return score;
    }

private:
    int w;
    int h;
    const std::vector<std::vector<int>> &food;
    std::deque<std::pair<int, int>> snake;
    std::unordered_set<int> body;
    int i{0};
    int score{0};

    inline int hash(int x, int y)
    {
        return x * 100000 + y;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
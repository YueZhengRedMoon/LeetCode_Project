#include <iostream>
#include <memory>
#include <deque>

namespace ErrorSolution
{
    struct Node
    {
        int value;
        std::shared_ptr<Node> prev{nullptr};
        std::shared_ptr<Node> next{nullptr};

        Node(int val = 0) : value(val) {}
    };

    class FrontMiddleBackQueue
    {
    public:
        FrontMiddleBackQueue() : head(std::make_shared<Node>()), tail(std::make_shared<Node>()), middle(nullptr)
        {
            init();
        }

        void pushFront(int val)
        {
            std::shared_ptr<Node> newNode = std::make_shared<Node>(val);

            newNode->next = head->next;
            newNode->prev = head;
            head->next->prev = newNode;
            head->next = newNode;

            ++size;
            if (size == 1)
            {
                middle = head->next;
            }
            else
            {
                if (size % 2 == 0)
                {
                    middle = middle->prev;
                }
            }
        }

        // 将元素插入到正中间的元素之前
        void pushMiddle(int val)
        {
            ++size;
            if (size == 1)
            {
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->next = tail;
                newNode->prev = head;
                head->next = newNode;
                tail->prev = newNode;
                middle = newNode;
            }
            else if (size == 3)
            {
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->prev = head->next;
                newNode->next = tail->prev;
                head->next->next = newNode;
                tail->prev->prev = newNode;
                middle = newNode;
            }
            else
            {
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->prev = middle->prev;
                newNode->next = middle;
                middle->prev->next = newNode;
                middle->prev = newNode;

                if (size % 2 == 0)
                    middle = middle->prev;
            }
        }

        void pushBack(int val)
        {
            ++size;
            if (size == 1)
            {
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->next = tail;
                newNode->prev = head;
                head->next = newNode;
                tail->prev = newNode;
                middle = newNode;
            }
            else if (size == 3)
            {
                std::shared_ptr<Node> newMiddle = middle->next;
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->prev = tail->prev;
                newNode->next = tail;
                tail->prev->next = newNode;
                tail->prev = newNode;
                middle = newMiddle;
            }
            else
            {
                std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
                newNode->prev = tail->prev;
                newNode->next = tail;
                tail->prev->next = newNode;
                tail->prev = newNode;

                if (size % 2 == 1)
                    middle = middle->next;
            }
        }

        int popFront()
        {
            if (size == 0)
                return -1;

            int frontValue = head->next->value;

            if (size == 1)
            {
                init();
            }
            else
            {
                --size;
                std::shared_ptr<Node> newMiddle = middle;
                if (size % 2 == 1)
                    newMiddle = middle->next;
                remove(head->next);
                middle = newMiddle;
            }

            return frontValue;
        }

        int popMiddle()
        {
            if (size == 0)
                return -1;

            int middleValue = middle->value;
            if (size == 1)
            {
                init();
            }
            else
            {
                --size;
                std::shared_ptr<Node> newMiddle;
                if (size % 2 == 1)
                    newMiddle = middle->next;
                else
                    newMiddle = middle->prev;
                remove(middle);
                middle = newMiddle;
            }

            return middleValue;
        }

        int popBack()
        {
            if (size == 0)
                return -1;

            int backValue = tail->prev->value;
            if (size == 1)
            {
                init();
            }
            else
            {
                --size;
                std::shared_ptr<Node> newMiddle = middle;
                if (size % 2 == 0)
                    newMiddle = middle->prev;
                remove(tail->prev);
                middle = newMiddle;
            }

            return backValue;
        }

        void printQueue()
        {
            auto node = head->next;
            while (node != tail)
            {
                std::cout << node->value << ' ';
                node = node->next;
            }
            std::cout << std::endl;
        }

    private:
        std::shared_ptr<Node> head;
        std::shared_ptr<Node> tail;
        std::shared_ptr<Node> middle;   // 指向正中间的元素
        std::size_t size;

        void init()
        {
            size = 0;
            head->next = tail;
            tail->prev = head;
            middle = tail;
        }

        void remove(std::shared_ptr<Node> &node)
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    };
}

class FrontMiddleBackQueue
{
public:
    FrontMiddleBackQueue() {}

    void pushFront(int val)
    {
        left.push_front(val);
        balance();
    }

    // 将元素插入到正中间的元素之前
    void pushMiddle(int val)
    {
        if (left.size() < right.size())
            left.push_back(val);
        else
            right.push_front(val);
        balance();
    }

    void pushBack(int val)
    {
       right.push_back(val);
        balance();
    }

    int popFront()
    {
        if (right.empty())
            return -1;

        int front;
        if (left.empty())
        {
            front = right.front();
            right.pop_front();
        }
        else
        {
            front = left.front();
            left.pop_front();
        }
        balance();

        return front;
    }

    int popMiddle()
    {
        if (right.empty())
            return -1;

        int middle;
        if (left.size() == right.size())
        {
            middle = left.back();
            left.pop_back();
        }
        else
        {
            middle = right.front();
            right.pop_front();
        }

        return middle;
    }

    int popBack()
    {
        if (right.empty())
            return -1;

        int back = right.back();
        right.pop_back();
        balance();
        return back;
    }

private:
    std::deque<int> left;
    std::deque<int> right;

    void balance()
    {
        // 调整长度，保证 0 <= right.size() - left.size() <= 1
        // 从而保证可以在正中间插入删除元素

        if (left.size() > right.size())
        {
            right.push_front(left.back());
            left.pop_back();
        }
        else if (right.size() > left.size() + 1)
        {
            left.push_back(right.front());
            right.pop_front();
        }
    }
};

int main()
{
    FrontMiddleBackQueue q;
    q.pushFront(1);   // [1]
    q.pushBack(2);    // [1, 2]
    q.pushMiddle(3);  // [1, 3, 2]
    q.pushMiddle(4);  // [1, 4, 3, 2]
    q.popFront();     // 返回 1 -> [4, 3, 2]
    q.popMiddle();    // 返回 3 -> [4, 2]
    q.popMiddle();    // 返回 4 -> [2]
    q.popBack();      // 返回 2 -> []
    q.popFront();     // 返回 -1 -> [] （队列为空）
    return 0;
}

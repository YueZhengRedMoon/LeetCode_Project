#include <iostream>
#include <vector>

class LRUCache
{
public:
    struct Node
    {
        int val;
        int key;
        Node *prev;
        Node *next;
        Node (int key_ = 0, int val_ = 0, Node *prev_ = nullptr, Node *next_ = nullptr)
        : key(key_), val(val_), prev(prev_), next(next_) {}
    };

    LRUCache(int capacity)
    : maxCapacity(capacity), size(0), front(new Node()), back(new Node())
    {
        front->next = back;
        back->prev = front;
    }

    ~LRUCache()
    {
        Node *p = front;
        while (p)
        {
            Node *toDel = p;
            p = p->next;
            delete toDel;
        }
    }

    int get(int key)
    {
        if (cache[key])
        {
            moveToFront(cache[key]);
            return cache[key]->val;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        if (cache[key])
        {
            moveToFront(cache[key]);
            cache[key]->val = value;
        }
        else
        {
            if (size >= maxCapacity)
            {
                Node *lru = back->prev;
                removeNode(lru);
                cache[lru->key] = nullptr;
                delete lru;
            }
            Node *newNode = new Node(key, value, front, front->next);
            front->next->prev = newNode;
            front->next = newNode;
            cache[key] = newNode;
            ++size;
        }
    }

private:
    static constexpr int MAX_K = 10001;
    std::vector<Node*> cache{std::vector<Node*>(MAX_K, nullptr)};
    int maxCapacity;
    int size;
    Node *front;
    Node *back;

    void moveToFront(Node *p)
    {
        removeNode(p);

        p->next = front->next;
        front->next->prev = p;
        p->prev = front;
        front->next = p;
    }

    void removeNode(Node *p)
    {
        Node *prev = p->prev;
        Node *next = p->next;
        next->prev = prev;
        prev->next = next;
    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}

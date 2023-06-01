#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Trie
{
public:
    struct Node
    {
        std::shared_ptr<Node> child[26]{nullptr};
        bool isEnd{false};
    };

    Trie() : root(std::make_shared<Node>()) {}

    void insert(std::string word)
    {
        std::shared_ptr<Node> cur = root;
        for (char c : word)
        {
            int index = getIndex(c);
            if (cur->child[index] == nullptr)
            {
                cur->child[index] = std::make_shared<Node>();
            }
            cur = cur->child[index];
        }
        cur->isEnd = true;
    }

    bool search(std::string word)
    {
        std::shared_ptr<Node> cur = root;
        for (char c : word)
        {
            int index = getIndex(c);
            if (cur->child[index] == nullptr)
            {
                return false;
            }
            cur = cur->child[index];
        }
        return cur->isEnd;
    }

    bool startsWith(std::string prefix)
    {
        std::shared_ptr<Node> cur = root;
        for (char c : prefix)
        {
            int index = getIndex(c);
            if (cur->child[index] == nullptr)
            {
                return false;
            }
            cur = cur->child[index];
        }
        return true;
    }

private:
    std::shared_ptr<Node> root;

    inline int getIndex(char c)
    {
        return c - 'a';
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}
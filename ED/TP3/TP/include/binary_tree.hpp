#ifndef TREE_H
#define TREE_H

#include <string>

typedef struct 
{
    int dest;
    int key;
    std::string message;

} Email;

class Node
{
    public:
        Node();
    
    private:
        Email email;
        Node * left;
        Node * right;

    friend class BinaryTree;
};

class BinaryTree
{
    public:
        BinaryTree();
        ~BinaryTree();

        void Insert(Email email);
        Email Search(int dest, int key);
        std::string Remove(int dest, int key);
        void Clean();

    private:
        void RecursiveInsert(Node* &p, Email email);
        std::string RecursiveDelete(Node* &p, int key1, int key2);
        Email RecursiveSearch(Node *p, int key1, int key2);
        void Predecessor(Node *q, Node* &r);
        void RecursiveClean(Node *p);

        Node * root;

};

#endif
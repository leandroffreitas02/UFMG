#ifndef HASH_H
#define HASH_H

#include "binary_tree.hpp"

class Hash_BT
{
    public:
        Hash_BT(int mod);
        void Insert(Email email);
        Email Search(int key1, int key2);
        std::string Remove(int key1, int key2);

    private:
        int M;
        int Hash(int key);
        BinaryTree * Table;

};

#endif
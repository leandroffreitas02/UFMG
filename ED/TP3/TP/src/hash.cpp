#include "hash.hpp"

Hash_BT::Hash_BT(int mod){
    M = mod;
    Table = (BinaryTree *) malloc(mod * sizeof(BinaryTree));
}
void Hash_BT::Insert(Email email){
    int pos = Hash(email.dest);

    Table[pos].Insert(email);
}
Email Hash_BT::Search(int key1, int key2){
    int pos = Hash(key1);

    return Table[pos].Search(key1, key2);
}
int Hash_BT::Hash(int key){
    return key % M;
}
std::string Hash_BT::Remove(int key1, int key2){
    int pos = Hash(key1);

    return Table[pos].Remove(key1, key2);
}
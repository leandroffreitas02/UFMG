#include "binary_tree.hpp"

Node::Node(){
    email.key = -1;
    left = NULL;
    right = NULL;
}

BinaryTree::BinaryTree(){
    root = NULL;
}
BinaryTree::~BinaryTree(){
    Clean();
}
void BinaryTree::Insert(Email email){
    RecursiveInsert(root, email);
}
void BinaryTree::RecursiveInsert(Node* &p, Email email)
// Descricao: insere um email na arvore binaria de forma recursiva
// Entrada: email
// Saida: nenhuma
{
    if(p == NULL){
        p = new Node();
        p->email = email;
    }
    else{
        if(email.key < p->email.key)
            RecursiveInsert(p->left, email);
        else
            RecursiveInsert(p->right, email);
    }
}
Email BinaryTree::Search(int key1, int key2){
    return RecursiveSearch(root, key1, key2);
}
Email BinaryTree::RecursiveSearch(Node *p, int key1, int key2)
// Descricao: pesquisa um email usando as chaves do remetente e do email, respectivamente
// Entrada: key1(chave remetente), key2(chave email)
// Saida: email correspondente
{
    Email aux;

    if(p == NULL){
        aux.key = -1;
        return aux;
    }
    if(key2 < p->email.key)
        return RecursiveSearch(p->left, key1, key2);
    else if(key2 > p->email.key)
        return RecursiveSearch(p->right, key1, key2);
    else{
        if(p->email.dest == key1)
            return p->email;
        
        else{
            aux.key = -1;
            return aux;
        }
    }
}
std::string BinaryTree::Remove(int key1, int key2){
    return RecursiveDelete(root, key1, key2);
}
std::string BinaryTree::RecursiveDelete(Node* &p, int key1, int key2)
// Descricao: busca e deleta um email
// Entrada: key1, key2
// Saida: string contendo a operação feita
{
    Node *aux;

    if(p == NULL)
        return "ERRO: MENSAGEM INEXISTENTE";
    
    if(key2 < p->email.key)
        return RecursiveDelete(p->left, key1, key2);
    else if(key2 > p->email.key)
        return RecursiveDelete(p->right, key1, key2);
    else if(key1 == p->email.dest){
        if(p->right == NULL){
            aux = p;
            p = p->left;
            free(aux);
        }
        else if(p->left == NULL){
            aux = p;
            p = p->right;
            free(aux);
        }
        else
            Predecessor(p, p->left);
            
        return "OK: MENSAGEM APAGADA";
    }
    else
        return "ERRO: MENSAGEM INEXISTENTE";
}
void BinaryTree::Predecessor(Node *q, Node* &r){
    if(r->right !=NULL){
        Predecessor(q, r->right);
        return;
    }

    q->email = r->email;
    q = r;
    r = r->left;
    free(q);
}
void BinaryTree::Clean(){
    RecursiveClean(root);
    root = NULL;
}
void BinaryTree::RecursiveClean(Node *p){
    if(p != NULL){
        RecursiveClean(p->left);
        RecursiveClean(p->right);
        delete p;
    }
}
#pragma once
#include "AVLNode.h"
#include <memory>
#include "Queue.h"

template<class T>
class AVLTree{
private:
    shared_ptr<AVLNode> root;  
    int size; 
public:
    AVLTree();
    AVLTree(AVLNode* root); 

    ~AVLTree();

    int getSize() const;

    void insert(int key);
    void erase(int key);

    bool empty() const; 

    int find() const; 
    int contains() const; 
};



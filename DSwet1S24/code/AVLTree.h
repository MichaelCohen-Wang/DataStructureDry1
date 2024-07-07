#pragma once
#include "AVLNode.h"
#include <memory>
#include "Queue.h"

template<class T>
class AVLTree{
private:
    shared_ptr<AVLNode> root;  
    int size; 
    Queue<int> keyQueue; 
public:
    AVLTree();
    AVLTree(AVLNode<T>* node); 

    ~AVLTree();

    int getSize() const;
    int getHeight() const; 
    //int findHeight(int key); 

    //maybe use static allocation array to create path
    //array size will be the height of the whole tree
    void insert(AVLNode<T> node);
    void erase(int key);

    bool empty() const; 

    int find() const; 
    int contains() const; 
};

template<class T>
AVLTree<T>::AVLTree(){
    root= nullptr; 
    size = 0;
}

/*
template<class T>
AVLTree<T>::AVLTree(AVLNode<T>* node){
    root = node; 
    size = 0;
}
*/

template<class T>
AVLTree<T>::~AVLTree() = default;

template<class T>
int AVLTree<T>::getSize() const{
    return size; 
}

template<class T>
int AVLTree<T>::getHeight() const{
    return root-> height; 
}




template<class T>
void AVLTree<T>::erase(int key){
    
}






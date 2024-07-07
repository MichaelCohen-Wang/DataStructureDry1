#pragma once
#include <memory>


template<class T>
struct AVLNode{
private:
    shared_ptr<AVLNode> leftNode; //left son 
    shared_ptr<AVLNode> rightNode; //right son
    int count; //#nodes in this tree
    int height; //height of node 
    T val; //node will hold pirate or ship
    int key; 

    AVLNode(int valueId);

    ~AVLNode(); 

    void setLeftNode(AVLNode* left); 
    void setRightNode(AVLNode* right);

    int findBalanceFactor();
    void fixValues(); //used to update values after rotation


    AVLNode* rotateLeft(); //LL rotation
    AVLNode* rotateRight(); //RR rotation




};
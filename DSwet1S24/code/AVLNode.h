#pragma once
#include <memory>


template<class T>
struct AVLNode{
private:
    std::shared_ptr<AVLNode> leftNode; //left son 
    std::shared_ptr<AVLNode> rightNode; //right son
    int count; //#nodes in this tree
    int height; //height of node 
    T val; //node will hold pirate or ship
    int key; 

    AVLNode(int valueId, T value);

    ~AVLNode(); 

    void setLeftNode(AVLNode* left); 
    void setRightNode(AVLNode* right);

    //page 24 lecture 4, if height of node doesn't change then BF doesn't either
    int findBalanceFactor() const;
    int updateHeight() const; 
    void fixValues(); //used to update values after rotation


    //AVLNode* rotateLeft(); //LL rotation
    //AVLNode* rotateRight(); //RR rotation
    std::shared_ptr<AVLNode<T>> rotateLeft();
    std::shared_ptr<AVLNode<T>> rotateRight();

};

template<class T>
AVLNode<T>::AVLNode(int valueId, T value): val(value){
leftNode = nullptr ;
rightNode = nullptr; 
count = 0;
height = 0;
key = valueId; 
}

template<class T>
AVLNode<T>::~AVLNode() = default; 

template<class T>
void AVLNode<T>::setLeftNode(AVLNode* left){
    leftNode = left; 
}

template<class T>
void AVLNode<T>::setRightNode(AVLNode* right){
    rightNode = right; 
}

template<class T>
int AVLNode<T>::findBalanceFactor() const{
    int left; 
    int right; 
    if(leftNode == nullptr){
        left = 0; 
    }
    else{
        left = leftNode.height;
    }

    if(rightNode == nullptr){
        right = 0; 
    }
    else{
        right = rightNode.height;
    }

    return left- right; 
}



template<class T>
void AVLNode<T>::fixValues(){ 
    {
    count = (leftNode != nullptr ? leftNode->count : 0) + (rightNode != nullptr ? rightNode->count : 0) + 1;
    
    height = std::max(leftNode != nullptr ? leftNode->height : 0, rightNode != nullptr ? rightNode->height : 0) + 1;
    //O(1) because we don't keep using getHeight function. We simply look at right and left members
}
}

//for this function to work, rightNode needs a leftNode
//check notebook diagram
template<class T>
std::shared_ptr<AVLNode<T>> AVLNode<T>::rotateLeft(){ //BF(v) = 2, BF(v_L) = -1
    std::shared_ptr<AVLNode<T>> right = rightNode; //holds onto rightNode even after reassignment
    this->rightNode = rightNode-> leftNode; //rightNode becomes rightNode's (bigger than this) leftNode (bigger than this but smaller than rightNode) 
    right -> leftNode  = this; 
    this.fixValues();
    right.fixValues();
    return right; 
}

//for this function to work, leftNode needs a rightNode
//same as rotateLeft but switches right and left
template<class T>
std::shared_ptr<AVLNode<T>> AVLNode<T>::rotateRight(){
    std::shared_ptr<AVLNode<T>> left = leftNode; //holds onto rightNode even after reassignment
    this->leftNode = leftNode-> rightNode; //rightNode becomes rightNode's (bigger than this) leftNode (bigger than this but smaller than rightNode) 
    left -> rightNode  = this; 
    this.fixValues();
    left.fixValues();
    return left; 

}
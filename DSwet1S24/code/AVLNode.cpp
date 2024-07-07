#include "AVLNode.h"

template<class T>
AVLNode::AVLNode(int valueId, T value): value(value){
leftNode = nullptr ;
rightNode = nullptr; 
count = 1;
height = 1;
key = valueId; 
}

template<class T>
AVLNode::~AVLNode() = default; 

template<class T>
void AVLNode::setLeftNode(AVLNode* left){
    leftNode = left; 
}

template<class T>
void AVLNode::setRightNode(AVLNode* right){
    rightNode = right; 
}

template<class T>
int AVLNode::findBalanceFactor() const{
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
void AVLNode::fixValues(){ 
    {
    count = (leftNode != nullptr ? leftNode->count : 0) + (rightNode != nullptr ? rightNode->count : 0) + 1;
    
    height = std::max(leftNode != nullptr ? leftNode->height : 0, rightNode != nullptr ? rightNode->height : 0) + 1;
}
}

//for this function to work, rightNode needs a leftNode
//check notebook diagram
template<class T>
void AVLNode::rotateLeft(){ //BF(v) = 2, BF(v_L) = -1
    AVLNode* right = rightNode; //holds onto rightNode even after reassignment
    this->rightNode = rightNode-> leftNode; //rightNode becomes rightNode's (bigger than this) leftNode (bigger than this but smaller than rightNode) 
    right -> leftNode  = this; 
    this.fixValues();
    right.fixValues()
}

//for this function to work, leftNode needs a rightNode
//same as rotateLeft but switches right and left
template<class T>
void AVLNode::rotateRight(){
    AVLNode* left = leftNode; //holds onto rightNode even after reassignment
    this->leftNode = leftNode-> rightNode; //rightNode becomes rightNode's (bigger than this) leftNode (bigger than this but smaller than rightNode) 
    left -> rightNode  = this; 
    this.fixValues();
    left.fixValues()

}



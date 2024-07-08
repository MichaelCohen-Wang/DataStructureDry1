#pragma once
#include "AVLNode.h"
#include <memory>
#include "Queue.h"

template<class T>
class AVLTree{
private:
    std::shared_ptr<AVLNode<T>> root;  
    int size; 
    Queue<int> keyQueue; 
public:
    AVLTree();
    AVLTree(AVLNode<T>* node); 

    ~AVLTree();

    int getSize() const;
    int getHeight() const; 
    //int findHeight(int key); 


    void insert(AVLNode<T> node);
    std::shared_ptr<AVLNode<T>> insertHelper(std::shared_ptr<AVLNode<T>> current, AVLNode<T> node);
    void erase(int key);
    std::shared_ptr<AVLNode<T>> eraseHelper(std::shared_ptr<AVLNode<T>> current, int key);



    bool empty() const; 

    int find(int key) const; 
    int findHelper(AVLNode<T>* current, int key) const;
    bool contains(int key) const; 
};

//global function: 
template<class T>
AVLNode<T>* balance(std::shared_ptr<AVLNode<T>> node);


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
AVLNode<T>* balance(std::shared_ptr<AVLNode<T>> node) {
  int balance = node->findBalanceFactor();

  // Left Left Case (Single right rotation)
  if(balance > 1 && node->leftNode->findBalanceFactor() >= 0) {
    return node->right_rotate();
  }

  // Left Right Case (Double left rotation)
  if(balance > 1 && node->leftNode->findBalanceFactor() < 0) {
    node->leftNode = node->leftNode->left_rotate();
    return node->right_rotate();
  }

  // Right Right Case (Single left rotation)
  if(balance < -1 && node->rightNode->findBalanceFactor() <= 0){
    return node->left_rotate();
  }

  // Right Left Case (Double right rotation)
  if(balance < -1 && node->rightNode->findBalanceFactor() > 0) {
    node->rightNode = node->rightNode->right_rotate();
    return node->left_rotate();
  }

  // No rotations needed
  return node;
}


template<class T>
void AVLTree<T>::erase(int key) {
  // Recursive helper function for deletion
  root = eraseHelper(root, key);
}


template<class T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::eraseHelper(std::shared_ptr<AVLNode<T>> current, int key) {
  // Base cases: Empty tree or key not found
  if (current == nullptr) {
    return nullptr; // Key not found
  }

  // Traverse based on key comparison
  if (key < current->key) {
    current->leftNode = eraseHelper(current->leftNode, key);
  } else if (key > current->key) {
    current->rightNode = eraseHelper(current->rightNode, key);
  } else {
    // Node found, handle deletion

    // Case 1: Node has no children (leaf node)
    if (current->leftNode == nullptr && current->rightNode == nullptr) {
      return nullptr; // Simply delete the leaf node
    }

    // Case 2: Node has one child
    if (current->leftNode == nullptr) {
      // One child on the right
      return current->rightNode; // Promote the right child
    } else if (current->rightNode == nullptr) {
      // One child on the left
      return current->leftNode; // Promote the left child
    }

    // Case 3: Node has two children (choose successor)
    // Find the in-order successor (smallest node in the right subtree)
    std::shared_ptr<AVLNode<T>> successor = current->rightNode;
    while (successor->leftNode != nullptr) {
      successor = successor->leftNode;
    }

    // Copy the value and key of the successor to the current node
    current->val = successor->val;
    current->key = successor->key;

    // Recursively delete the successor (backtracking)
    current->rightNode = eraseHelper(current->rightNode, successor->key);
  }

  // Update height after deletion (may have changed)
  current->fixValues();

  // Perform rotations for balance (implementation details omitted)
  return balance(current);
}

void insert(AVLNode<T> node){
  // Recursive helper function for deletion
  root = eraseHelper(root, node);
}

template<class T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::insertHelper(std::shared_ptr<AVLNode<T>> current, AVLNode<T> node) {
  // Base case: Empty tree
  if (current == nullptr) {
    return std::make_shared<AVLNode<T>>(node.key, node.val);
  }

  // Traverse based on key comparison
  if (node.key < current->key) {
    current->leftNode = insertHelper(current->leftNode, node);
  } else if (node.key > current->key) {
    current->rightNode = insertHelper(current->rightNode, node);
  }

  // Update height of the current node
  current->fixValues();

  return balance(current);
}

template<class T>
bool AVLTree<T>::empty() const {
  return root == nullptr; // Check if the root is nullptr (empty tree)
}

template<class T>
int AVLTree<T>::find(int key) const {
  // Recursive helper function for finding a node with the given key
  return findHelper(root, key);
}

template<class T>
int AVLTree<T>::findHelper(AVLNode<T>* current, int key) const {
  // Base cases: Empty tree or key not found
  if (current == nullptr) {
    return -1; // Key not found
  }

  // Traverse based on key comparison
  if (key < current->key) {
    return findHelper(current->leftNode, key);
  } else if (key > current->key) {
    return findHelper(current->rightNode, key);
  } else {
    // Key found! Return the value associated with the key
    return current->val;
  }
}

// Function for checking existence (similar to find, returns true/false)
template<class T>
bool AVLTree<T>::contains(int key) const {
  return find(key) != -1; // If find returns -1 (not found), contains returns false
}



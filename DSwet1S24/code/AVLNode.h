#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>

template<class T>
struct AVLNode {
  AVLNode<T>* leftNode;  // Left child
  AVLNode<T>* rightNode; // Right child
  int count;             // Number of nodes in the subtree rooted at this node
  int height;            // Height of the node
  T val;                // Value stored in the node
  int key;               // Key of the node

  AVLNode(int valueId, T value);
  ~AVLNode();

  void setLeftNode(AVLNode* left);
  void setRightNode(AVLNode* right);

  // Page 24 lecture 4, if height of node doesn't change then BF doesn't either
  int findBalanceFactor() const;
  int updateHeight() const;
  void fixValues(); // Used to update values after rotation

  AVLNode<T>* rotateLeft(); // LL rotation
  AVLNode<T>* rotateRight(); // RR rotation
};

template<class T>
AVLNode<T>::AVLNode(int valueId, T value) : val(value) {
  leftNode = nullptr;
  rightNode = nullptr;
  count = 1;
  height = 1;
  key = valueId;
}

template<class T>
AVLNode<T>::~AVLNode() {
  // Manual memory deallocation required to avoid leaks
  // Implement logic to delete left and right nodes recursively
  // Consider using a separate helper function for deletion
}

template<class T>
void AVLNode<T>::setLeftNode(AVLNode* left) {
  leftNode = left;
}

template<class T>
void AVLNode<T>::setRightNode(AVLNode* right) {
  rightNode = right;
}

template<class T>
int AVLNode<T>::findBalanceFactor() const {
  int left = leftNode != nullptr ? leftNode->height : 0;
  int right = rightNode != nullptr ? rightNode->height : 0;

  return left - right;
}

template<class T>
void AVLNode<T>::fixValues() {
  count = (leftNode != nullptr ? leftNode->count : 0) +
         (rightNode != nullptr ? rightNode->count : 0) + 1;

  height = std::max(leftNode != nullptr ? leftNode->height : 0,
                   rightNode != nullptr ? rightNode->height : 0) +
          1;
}

template<class T>
AVLNode<T>* AVLNode<T>::rotateLeft() { // BF(v) = 2, BF(v_L) = -1
  AVLNode<T>* right = rightNode; // Hold onto rightNode even after reassignment
  this->rightNode = rightNode->leftNode; // RightNode becomes rightNode's (bigger than this) leftNode (bigger than this but smaller than rightNode)
  right->leftNode = this;                 // RightNode's leftNode becomes this (current node)
  this->fixValues();
  right->fixValues();
  return right;
}

template<class T>
AVLNode<T>* AVLNode<T>::rotateRight() { // BF(v) = -2, BF(v_R) = 1
  AVLNode<T>* left = leftNode;   // Hold onto leftNode even after reassignment
  this->leftNode = leftNode->rightNode; // LeftNode becomes leftNode's (bigger than this) rightNode (bigger than this but smaller than leftNode)
  left->rightNode = this;               // LeftNode's rightNode becomes this (current node)
  this->fixValues();
  left->fixValues();
  return left;
}
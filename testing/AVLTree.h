#pragma once
#include "AVLNode.h"

template<class T>
class AVLTree {
private:
  
  int size;
public:
//set to public for testing
  AVLNode<T>* root;



  AVLTree();
  AVLTree(AVLNode<T>* node); // This constructor might not be safe anymore (see note)

  ~AVLTree();

  int getSize() const {
    return size;
  }

  int getHeight() const {
    return root->height;
  }

  //int findHeight(int key); 

  //insert for nodes: 
  void insert(AVLNode<T> node);
  AVLNode<T>* insertHelper(AVLNode<T>* current, AVLNode<T> node);
  //insert for pointers: 
  void insert(AVLNode<T>* node);
  AVLNode<T>* insertHelper(AVLNode<T>* current, AVLNode<T>* node);
  void erase(int key);
  AVLNode<T>* eraseHelper(AVLNode<T>* current, int key);

  AVLNode<T>* eraseHelper(AVLNode<T>* current, T key);
  void erase(T check);
  bool empty() const;

  AVLNode<T>* find(int key) const;

  AVLNode<T>* findHelper(AVLNode<T>* current, int key) const;

  void deleteHelper(AVLNode<T>* current);

  // Function for checking existence (similar to find, returns true/false)
  bool contains(int key) const;

  //maybe will cause problems when we remove in following method
  AVLNode<T>* getMaximum() const;

  AVLNode<T>* getMinimum() const;

  void printTree(AVLNode<T>* root, int space) const{
      // Base case
      if (root == NULL)
          return;
  
      // Increase distance between levels
      space += 5;
  
      // Process right child first
      printTree(root->rightNode, space);
  
      // Print current node after space
      // count
      std::cout << std::endl;
      for (int i = 5; i < space; i++)
          std::cout << " ";
      std::cout << root->key << "\n";
  
      // Process left child
      printTree(root->leftNode, space);
  }
 
  void print() const
  {
      if (!root)
      {
          std::cout << "Tree is empty.\n";
          return;
      }
      printTree(root, 0);
  }

};
//global function: 
template<class T>
AVLNode<T>* balance(AVLNode<T>* node) {
  // Get the balance factor of the node
  int balanceFactor = node->findBalanceFactor();

  if (balanceFactor > 1) {
    // Left-Left (LL) imbalance: Perform a right rotation on the current node
    if (node->leftNode != nullptr && node->leftNode->findBalanceFactor() >= 0) {
      return node->rotateRight();
    }
    // Left-Right (LR) imbalance: Perform a left rotation on the child first, then a right rotation on the current node
    else {
      node->leftNode = node->leftNode->rotateLeft();
      return node->rotateRight();
    }
  }

  // Handle right-heavy imbalances
  if (balanceFactor < -1) {
    // Right-Right (RR) imbalance: Perform a left rotation on the current node
    if (node->rightNode != nullptr && node->rightNode->findBalanceFactor() <= 0) {
      return node->rotateLeft();
    }
    // Right-Left (RL) imbalance: Perform a right rotation on the child first, then a left rotation on the current node
    else {
      node->rightNode = node->rightNode->rotateRight();
      return node->rotateLeft();
    }
  }

  // Node is balanced, no rotations needed
  return node;
}


template<class T>
AVLTree<T>::AVLTree() {
  root = nullptr;
  size = 0;
}


template<class T>
AVLTree<T>::AVLTree(AVLNode<T>* node) {
  // This constructor might not be safe anymore
  // Assigning a raw pointer directly can lead to memory leaks
  // Consider using std::make_shared or manual memory management
  root = node;
  size = 0;
}

template<class T>
void AVLTree<T>::insert(AVLNode<T> node) {
  // Recursive helper function for insertion
  
  if(this->contains(node->key)){
    return; 
  }

  root = insertHelper(root, node);
  size++; // Increment size after successful insertion
}

// makes a copy of node and doesn't release it - bad
template<class T>
AVLNode<T>* AVLTree<T>::insertHelper(AVLNode<T>* current, AVLNode<T> node) {
  // Base case: Empty tree
  if (current == nullptr) {
    // Allocate memory for new node (assuming raw pointers)
    return new AVLNode<T>(node.key, node.val);
  }

  // Traverse based on key comparison
  if (node.key < current->key) {
    // Check for null pointer before accessing leftNode
    if (current->leftNode == nullptr) {
      current->leftNode = new AVLNode<T>(node.key, node.val); // Allocate for left child
    } else {
      current->leftNode = insertHelper(current->leftNode, node);
    }
  } 
  else if (node.key > current->key) {
    // Check for null pointer before accessing rightNode
    if (current->rightNode == nullptr) {
      current->rightNode = new AVLNode<T>(node.key, node.val); // Allocate for right child
    } else {
      current->rightNode = insertHelper(current->rightNode, node);
  }
  }
  // Update height of the current node
  current->fixValues();
  return balance(current);
}


template<class T>
void AVLTree<T>::insert(AVLNode<T>* node) {
  // Recursive helper function for insertion
  /*
  if(this->contains(node->key)){
    return;
  }
  */
  if(root != nullptr){
    root = insertHelper(root, node);
    size++;
  }
  else{
    root = node; 
    size++;
  }
 // Increment size after successful insertion
}

template<class T>
AVLNode<T>* AVLTree<T>::insertHelper(AVLNode<T>* current, AVLNode<T>* node) {
  // Base case: Empty tree

  // Traverse based on key comparison
  if (node->key < current->key) {
    // Check for null pointer before accessing leftNode
    if (current->leftNode == nullptr) {
      current->leftNode = node; 
    } else {
      current->leftNode = insertHelper(current->leftNode, node);
    }
  } 
  else if (node->key > current->key) {
    // Check for null pointer before accessing rightNode
    if (current->rightNode == nullptr) {
      current->rightNode = node; 
    } else {
      current->rightNode = insertHelper(current->rightNode, node);
    }
  }
  else{
    if(current -> val < node -> val){
      if (current->rightNode == nullptr) {
        current->rightNode = node; 
      } else {
        current->rightNode = insertHelper(current->rightNode, node);
      }
    }
    else{
      if (current->leftNode == nullptr) {
        current->leftNode = node; 
      } else {
      current->leftNode = insertHelper(current->leftNode, node);
      }
    }
  }
  // Update height of the current node
  current->fixValues();
  return balance(current);
}



template<class T>
AVLNode<T>* AVLTree<T>::eraseHelper(AVLNode<T>* current, int key) {
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

    // Case 1: Node has
        // Case 1: Node has no children (leaf node)
    if (current->leftNode == nullptr && current->rightNode == nullptr) {
      
      delete current; // Manually deallocate memory for the leaf node
      return nullptr;
    }

    // Case 2: Node has one child
    if (current->leftNode == nullptr) {
      // One child on the right
      AVLNode<T>* temp = current;
      current = current->rightNode;
      delete temp; // Delete the current node
      return current;
    } else if (current->rightNode == nullptr) {
      // One child on the left
      AVLNode<T>* temp = current;
      current = current->leftNode;
      delete temp; // Delete the current node
      return current;
    }

    // Case 3: Node has two children (choose successor)
    // Find the in-order successor (smallest node in the right subtree)
        AVLNode<T>* successor = current->rightNode;
        AVLNode<T>* successorParent = current;
  
        // Find the leftmost leaf in the right subtree
        while (successor->leftNode != nullptr) {
            successorParent = successor;
            successor = successor->leftNode;
        }
        // If successor is not the immediate right child
        if (successorParent != current) {
            successorParent->leftNode = successor->rightNode;
            successor->rightNode = current->rightNode;
        }
        successor->leftNode = current->leftNode;
        
        // Delete current node
        delete current;
        current = successor;
  }

  // Update height after deletion (may have changed)
  if(current != nullptr){
    current->fixValues();
  }

  // Perform rotations for balance (implementation details omitted)
  return balance(current);
}

template<class T>
void AVLTree<T>::erase(int key) {
  //std::cout << "called here" << std::endl; 
  //std::cout.flush();
  if(!this->contains(key)){
    return; 
  }
  // Recursive helper function for deletion
  root = eraseHelper(root, key);
  size--; 
}


template<class T>
AVLNode<T>* AVLTree<T>::eraseHelper(AVLNode<T>* current, T key) {
  // Base cases: Empty tree or key not found
  if (current == nullptr) {
    return nullptr; // Key not found
  }
  // Traverse based on key comparison
  //only sorting by Id which is in different order
  if (key <= current->val) {
    //std::cout << "I was here 1" << std::endl; 
    current->leftNode = eraseHelper(current->leftNode, key);
  } else if (key >= current->val) {
    //std::cout << "I was here 2" << std::endl; 
    current->rightNode = eraseHelper(current->rightNode, key);
  } else {
    //std::cout << "I was here 3" << std::endl; 
    // Node found, handle deletion

    // Case 1: Node has
        // Case 1: Node has no children (leaf node)
    if (current->leftNode == nullptr && current->rightNode == nullptr) {
      //std::cout << "I was here 4" << std::endl; 
      delete current; // Manually deallocate memory for the leaf node
      return nullptr;
    }

    // Case 2: Node has one child
    if (current->leftNode == nullptr) {
      // One child on the right
      //std::cout << "I was here 5" << std::endl; 
      AVLNode<T>* temp = current;
      current = current->rightNode;
      delete temp; // Delete the current node
      return current;
    } else if (current->rightNode == nullptr) {
      // One child on the left
      AVLNode<T>* temp = current;
      current = current->leftNode;
      delete temp; // Delete the current node
      return current;
    }

    // Case 3: Node has two children (choose successor)
    // Find the in-order successor (smallest node in the right subtree)
        AVLNode<T>* successor = current->rightNode; AVLNode<T>* successorParent = current;
  
        // Find the leftmost leaf in the right subtree
        while (successor->leftNode != nullptr) {
            successorParent = successor;
            successor = successor->leftNode;
        }
        if (successorParent != current) {successorParent->leftNode = successor->rightNode; successor->rightNode = current->rightNode;}
        successor->leftNode = current->leftNode;
        
        delete current;
        current = successor;
  }

  // Update height after deletion (may have changed)
  
  current->fixValues();

  return balance(current);
}

template<class T>
void AVLTree<T>::erase(T check) {
  // Recursive helper function for deletion
  root = eraseHelper(root, check);
  size--; 
}

// Destructor implementation (mentioned earlier)

template<class T>
AVLTree<T>::~AVLTree() {
  //std::cout << "destroy" << std::endl;
  if(root == nullptr){
    return;
  }
  
  // Recursive helper function to delete all nodes in the tree
  deleteHelper(root);
}


// Helper function for destructor
template<class T>
void AVLTree<T>::deleteHelper(AVLNode<T>* current) {
  if (current == nullptr) {
    return;
  }
  deleteHelper(current->leftNode);
  deleteHelper(current->rightNode);
  delete current; // Delete the current node
}

template<class T>
bool AVLTree<T>::empty() const {
  return root == nullptr; // Check if the root is nullptr (empty tree)
}

template<class T>
AVLNode<T>* AVLTree<T>::find(int key) const {
  // Recursive helper function for finding a node with the given key
  return findHelper(root, key);
}

template<class T>
AVLNode<T>* AVLTree<T>::findHelper(AVLNode<T>* current, int key) const {
  // Base cases: Empty tree or key not found
  if (current == nullptr) {
    return nullptr; // Key not found
  }
  // Traverse based on key comparison
  if (key < current->key) {
    return findHelper(current->leftNode, key);
  } else if (key > current->key) {
    return findHelper(current->rightNode, key);
  } else {
    // Key found! Return the node
    return current;
  }
}

template<class T>
bool AVLTree<T>::contains(int key) const {
  // If find returns nullptr (not found), contains returns false
  return find(key) != nullptr; 

}

template<class T>
AVLNode<T>* AVLTree<T>::getMaximum() const{
  if(root == nullptr){
    return nullptr; 
  }

  AVLNode<T>* current = root;
  while(current->rightNode !=nullptr){
      current = current->rightNode; 
  }
  return current; 
}

template<class T>
AVLNode<T>* AVLTree<T>::getMinimum() const{
  if(root == nullptr){
    return nullptr; 
  }

  AVLNode<T>* current = root;
  while(current->leftNode !=nullptr){
      current = current->leftNode; 
  }
  return current; 
}

template<class T>
void swapValues(AVLNode<T>* a, AVLNode<T>* b) {
    T tempKey = a->key;
    T tempVal = a->val;
    a->key = b->key;
    a->val = b->val;
    b->key = tempKey;
    b->val = tempVal;
}


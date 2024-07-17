#pragma once 

#include "pirates24b1.h"
#include "wet1util.h"
#include "AVLNode.h"
#include "AVLTree.h"
#include "Pirate.h"


class Ship {
public:
    int m_counter=0;
    int m_shipId;
    int m_cannons;
    int m_battleWinnings; 
    AVLTree<Pirate> pirates_index ; //the tree is by index of pirates(queue)
    AVLTree<Pirate> pirates_id ;
    AVLTree<Pirate> pirates_treasure ;
    Pirate* m_richestPirate; 
    int m_currentIndex=-100000;
    Ship(const int id, int cannons = 0, int counter=0);
    // int exist(int shipId);
 
    // Additional fields and methods
};
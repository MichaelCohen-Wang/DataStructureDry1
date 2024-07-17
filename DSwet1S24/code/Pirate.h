#pragma once 
#include "AVLNode.h"
#include "AVLTree.h"
#include <memory>
#include "Ship.h"

class Ship; 

class Pirate {
   
    
public:
    int m_pirateId;
    int m_treasure;
    int m_pirateIndex;
    int m_shipId;
    std::shared_ptr<Ship> m_ship;
    bool operator<(Pirate other); 
    bool operator>(Pirate other); 

    Pirate(const int id, int treasure, int pirateIndex, int shipid);
    // Additional fields 
};
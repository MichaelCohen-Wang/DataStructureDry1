#pragma once 
#include "AVLNode.h"
#include "AVLTree.h"
#include <memory>
#include "Ship.h"

class Pirate {
private:
   
    
public:
    int m_pirateId;
    int m_treasure;
    int m_pirateIndex;
    int m_shipId;
    std::shared_ptr<Ship> m_ship;

    Pirate(const int id, int treasure, int pirateIndex, int shipid);
    // Additional fields 
};
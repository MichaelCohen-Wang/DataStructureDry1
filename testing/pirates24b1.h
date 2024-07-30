#pragma once
#include "pirates24b1.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"
#include "Ship.h"

class Ship;

class Pirate {
public:
    int m_pirateId;
    int m_treasure;
    int m_pirateIndex;
    int m_shipId;
    Ship* m_ship;

    bool operator<(Pirate other); 
    bool operator>(Pirate other); 

    bool operator<=(Pirate other);
    bool operator>=(Pirate other);
    Pirate(const int id, int treasure, int pirateIndex, int shipid);
    // Additional fields 
};


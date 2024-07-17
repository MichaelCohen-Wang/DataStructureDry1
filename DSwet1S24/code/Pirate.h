#pragma once
#include "pirates24b1.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"
#include "Ship.h"


class Pirate {
public:
    int m_pirateId;
    int m_treasure;
    int m_pirateIndex;
    int m_shipId;
    Ship* m_ship;

    Pirate(const int id, int treasure, int pirateIndex, int shipid);
    // Additional fields 
};
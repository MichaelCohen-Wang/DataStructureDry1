
#pragma once 

#include "Ship.h"
#include "wet1util.h"
#include "AVLNode.h"
#include "AVLTree.h"
#include "Pirate.h"

class Ocean {
private:

    AVLTree<Ship> ship_head;
    AVLTree<Pirate> pirate_head;


public:
    // <DO-NOT-MODIFY> {
    
    Ocean();

    virtual ~Ocean();
    
    StatusType add_ship(int shipId, int cannons);

    StatusType remove_ship(int shipId);
    
    StatusType add_pirate(int pirateId, int shipId, int treasure);
    
    StatusType remove_pirate(int pirateId);
    
    StatusType treason(int sourceShipId, int destShipId);

    StatusType update_pirate_treasure(int pirateId, int change);

    output_t<int> get_treasure(int pirateId);

    output_t<int> get_cannons(int shipId);

    output_t<int> get_richest_pirate(int shipId);

    StatusType ships_battle(int shipId1,int shipId2);

  
};


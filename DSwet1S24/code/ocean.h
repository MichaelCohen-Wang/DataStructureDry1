
#ifndef OCEAN
#define OCEAN

#include "wet1util.h"
#include "AVLNode.h"
#include "AVLTree.h"




class Pirate {
private:
   
    
public:
    int m_pirateId;
    int m_treasure;
    int m_pirateIndex;
    int m_shipId;
    Ship *m_ship;

    Pirate(const int id, int treasure, int pirateIndex, int shipid);
    // Additional fields 
};

class Ship {
private:      


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

#endif // PIRRATES

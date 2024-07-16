#include "ocean.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"


//pirate constr'
Pirate::Pirate(const int id, int treasure, int pirateIndex, int shipId):
m_pirateId(id), m_treasure(treasure), m_pirateIndex(pirateIndex),m_shipId(shipId),m_ship(nullptr){}

//ship constr'
Ship::Ship(const int id, int cannons,int counter): 
  m_shipId(id), m_cannons(cannons), m_counter(counter){}

/*int Ship::exist(int id){

}
*/

//---------------------------OCEAN class------------------------
StatusType Ocean::add_ship(int shipId, int cannons)
{
    
    if(shipId <= 0 || cannons < 0){//invalid input =2
    return StatusType(2);
    }

    if(this->ship_head.contains(shipId))// failure
        return StatusType(3);
        
    Ship new_ship = Ship(shipId,cannons); //do we need to do a pointer
    try{  
        AVLNode<Ship>* newleaf = new AVLNode<Ship>(shipId,new_ship);
        this->ship_head.insert((newleaf));
        return StatusType(0); //success  
    }
    catch (...){ // bad alloc allocation error=1
        return StatusType(1);
    }
}

StatusType Ocean::remove_ship(int shipId) // check counter =0
{
    if(shipId <= 0)//invalid input =2
        return StatusType(2);

    if(this->ship_head.contains(shipId)&&(this->ship_head.find(shipId))->val.m_counter==0){
        this->ship_head.erase((shipId));//delete empty ship
        return StatusType(0);
    }
    return StatusType(3); //failure
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure){


    if(shipId <= 0 || pirateId <= 0){//invalid input =2
    return StatusType(2);
    }

    if(!this->ship_head.contains(shipId))// failure no such ship
        return StatusType(3);

    AVLNode<Ship>* current_ship = this->ship_head.find(shipId);
   
    if(current_ship->val.pirates_id.contains(pirateId) ){
        return StatusType(3);  //already exist
    }
    Pirate new_pirate1 = Pirate(pirateId,treasure, current_ship->val.m_currentIndex,current_ship->key); //do we need to do a pointer
    new_pirate1.m_ship= &current_ship->val; //to have a pointer to the ship
    Pirate new_pirate2 = new_pirate1;//for index
    Pirate new_pirate3 = new_pirate1;//for treasure
    Pirate new_pirate4 = new_pirate1;//for ocean


    try{  
        AVLNode<Pirate>* pirateleaf = new AVLNode<Pirate>(pirateId,new_pirate4);//for all the piraes in the ocean
        this->pirate_head.insert((pirateleaf));

        AVLNode<Pirate>* idPirate = new AVLNode<Pirate>(pirateId, new_pirate1);
        AVLNode<Pirate>* indexPirate = new AVLNode<Pirate>(current_ship->val.m_currentIndex, new_pirate2);
        AVLNode<Pirate>* treasurePirate = new AVLNode<Pirate>(treasure, new_pirate3);
        current_ship->val.pirates_id.insert(idPirate);//add the pirates to the tree
        current_ship->val.pirates_index.insert(indexPirate);
        current_ship->val.pirates_treasure.insert(treasurePirate);
        current_ship->val.m_currentIndex ++;
        current_ship->val.m_counter++;
        return StatusType(0); //success  
    }
    catch (...){ // bad alloc allocation error=1
        return StatusType(1);
    }
    return StatusType(0);
}
    
StatusType Ocean::remove_pirate(int pirateId){


}
    
    StatusType treason(int sourceShipId, int destShipId);

    StatusType update_pirate_treasure(int pirateId, int change);

    output_t<int> get_treasure(int pirateId);

    output_t<int> get_cannons(int shipId);

    output_t<int> get_richest_pirate(int shipId);

    StatusType ships_battle(int shipId1,int shipId2);



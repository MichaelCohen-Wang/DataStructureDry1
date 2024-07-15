#include "Ocean.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"


//pirate constr'
Pirate::Pirate(const int id, int treasure, int pirateIndex):
     pirateId_n(id), treasure_n(treasure), pirate_index_n(pirateIndex){}

//ship constr'
Ship::Ship(const int id, int cannons): shipId_m(id), cannons_m(cannons){}

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

StatusType Ocean::remove_ship(int shipId)
{
    if(shipId <= 0)//invalid input =2
        return StatusType(2);

    if(this->ship_head.contains(shipId)){
        this->ship_head.erase((shipId));
        return StatusType(0);
    }
    return StatusType(3);
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure){


    if(shipId <= 0 || pirateId <= 0){//invalid input =2
    return StatusType(2);
    }

    if(!this->ship_head.contains(shipId))// failure no such ship
        return StatusType(3);

    AVLNode<Ship>* current_ship = this->ship_head.find(shipId);
   
    if(current_ship->val.pirates_id.contains(pirateId) ){
        return StatusType(3);
    }
    Pirate new_pirate1 = Pirate(pirateId,treasure, current_ship->val.current_index); //do we need to do a pointer
    Pirate new_pirate2 = Pirate(pirateId,treasure, current_ship->val.current_index);

    try{  
        AVLNode<Pirate>* idPirate = new AVLNode<Pirate>(pirateId, new_pirate1);
        AVLNode<Pirate>* indexPirate = new AVLNode<Pirate>(current_ship->val.current_index, new_pirate2);
        current_ship->val.pirates_id.insert(idPirate);
        current_ship->val.pirates_index.insert(indexPirate);
        current_ship->val.current_index ++; 
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



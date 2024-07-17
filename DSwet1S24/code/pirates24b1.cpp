#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"
#include "pirates24b1.h"

//pirate constr'
Pirate::Pirate(const int id, int treasure, int pirateIndex, int shipId):
m_pirateId(id), m_treasure(treasure), m_pirateIndex(pirateIndex),m_shipId(shipId),m_ship(nullptr){}

//ship constr'
Ship::Ship(const int id, int cannons,int counter): 
  m_shipId(id), m_cannons(cannons), m_battleWinnings(0), m_counter(counter){}

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
        
    std::shared_ptr<Ship> new_ship = std::make_shared<Ship>(shipId, cannons);
    try{  
        AVLNode<Ship>* newleaf = new AVLNode<Ship>(shipId, new_ship);
        this->ship_head.insert(newleaf);
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

    if(this->ship_head.contains(shipId)&& this->ship_head.find(shipId)->val->m_counter==0){
        this->ship_head.erase((shipId));//delete empty ship
        return StatusType(0);
    }
    return StatusType(3); //failure
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure){


    if(shipId <= 0 || pirateId <= 0){//invalid input =2
    return StatusType(2);
    }

    if(!this->ship_head.contains(shipId) || !this->pirate_head.contains(pirateId))// failure no such ship
        return StatusType(3);

    AVLNode<Ship>* current_ship = this->ship_head.find(shipId);
   
    if(current_ship->val->pirates_id.contains(pirateId) ){
        return StatusType(3);  //already exist
    }
    std::shared_ptr<Pirate> new_pirate = std::make_shared<Pirate>(pirateId,treasure - current_ship->val->m_battleWinnings, current_ship->val->m_currentIndex,current_ship->key); //do we need to do a pointer
    new_pirate-> m_ship= current_ship->val; //to have a pointer to the ship


    try{  
        AVLNode<Pirate>* idPirate = new AVLNode<Pirate>(pirateId, new_pirate);
        AVLNode<Pirate>* indexPirate = new AVLNode<Pirate>(current_ship->val->m_currentIndex, new_pirate);
        AVLNode<Pirate>* treasurePirate = new AVLNode<Pirate>(treasure, new_pirate);
        AVLNode<Pirate>* oceanPirate = new AVLNode<Pirate>(pirateId, new_pirate);
        current_ship->val->pirates_id.insert(idPirate);//add the pirates to the tree
        current_ship->val->pirates_index.insert(indexPirate);
        current_ship->val->pirates_treasure.insert(treasurePirate);
        pirate_head.insert(oceanPirate);
        if(current_ship->val->pirates_index.empty()){
            //no need to free because new_pirate4 wasn't dynmically allocated
            current_ship->val->m_richestPirate = new_pirate;
        }
        else{
            if(current_ship->val->m_richestPirate->m_treasure < treasure){
                current_ship->val->m_richestPirate = new_pirate;
            }
            else if(current_ship->val->m_richestPirate->m_treasure == treasure){
                if(current_ship->val->m_richestPirate->m_pirateId < pirateId){
                    current_ship->val->m_richestPirate = new_pirate;
                }
            }
        }
        current_ship->val->m_currentIndex ++;
        current_ship->val->m_counter++;
        return StatusType(0); //success  
    }
    catch (...){ // bad alloc allocation error=1
        return StatusType(1);
    }
    return StatusType(0);
}
    
StatusType Ocean::remove_pirate(int pirateId){
    if(pirateId <= 0){//invalid input =2
        return StatusType(2);
    }


    if(!this->pirate_head.contains(pirateId))// failure no such ship
        return StatusType(3);
    
    
    
    AVLNode<Pirate>* target = pirate_head.find(pirateId); 
    std::shared_ptr<Ship> out = target->val->m_ship;
    //need to figure out how to do get richest pirate for remove
    if(out->m_richestPirate == target->val){

    }

    out->pirates_id.erase(target->val->m_pirateId);
    out->pirates_index.erase(target->val->m_pirateIndex);
    out->pirates_treasure.erase(target->val->m_treasure);
    out->m_counter--; 

    pirate_head.erase(pirateId);
    return StatusType(0);
}
    
StatusType Ocean::treason(int sourceShipId, int destShipId){
    if(sourceShipId<= 0 || destShipId<= 0){//invalid input =2
        return StatusType(2);
    }
   if(!this->ship_head.contains(sourceShipId) || !this->ship_head.contains(destShipId))// failure no such ship
        return StatusType(3);

    AVLNode<Ship>* sourceShip = this->ship_head.find(sourceShipId);
    AVLNode<Ship>* destShip = this->ship_head.find(destShipId);

    AVLNode<Pirate>* oldest = sourceShip->val->pirates_index.getMinimum();
    AVLNode<Pirate>* oldestCash = pirate_head.find(oldest->val->m_pirateId);
    int oldestId = oldest->val->m_pirateId;
    int oldestTreasure = oldestCash->val->m_treasure + sourceShip->val->m_battleWinnings;

    remove_pirate(oldestId);

    add_pirate(oldestId, destShip->val->m_shipId, oldestTreasure);

    return StatusType(0);
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change){
   if(pirateId <= 0){//invalid input =2
        return StatusType(2);
    }

    if(!this->pirate_head.contains(pirateId))// failure no such ship
        return StatusType(3);

    AVLNode<Pirate>* target = pirate_head.find(pirateId);

    std::shared_ptr<Ship> targetShip = target->val->m_ship;

    targetShip->pirates_treasure.erase(target->val->m_treasure); 
    target->val->m_treasure += change; 
    AVLNode<Pirate>* newNode= new AVLNode<Pirate>(pirateId, target->val);
    targetShip->pirates_treasure.insert(newNode); 

    if(targetShip->pirates_index.empty()){
        //no need to free because new_pirate4 wasn't dynmically allocated
        targetShip->m_richestPirate = target->val;
    }
    else{
        if(targetShip->m_richestPirate->m_treasure < target->val->m_treasure){
            targetShip->m_richestPirate = target->val;
        }
        else if(targetShip->m_richestPirate->m_treasure == target->val->m_treasure){
            if(targetShip->m_richestPirate->m_pirateId < pirateId){
                targetShip->m_richestPirate = target->val;
            }
        }
    }
    return StatusType(0);


}

output_t<int> Ocean::get_treasure(int pirateId){
    if(pirateId <= 0){
        return StatusType(2);
    }
    if(!pirate_head.contains(pirateId)){
        return StatusType(3);
    }
    AVLNode<Pirate>* targetPirate = pirate_head.find(pirateId);
    std::shared_ptr<Ship> current_ship = targetPirate->val->m_ship; 
    //add winnings gained in fights
    return output_t<int>(targetPirate->val->m_treasure + current_ship->m_battleWinnings); 
}


output_t<int> Ocean::get_cannons(int shipId){
    if(shipId <= 0 ){
        return StatusType(2);
    }
    if(!ship_head.contains(shipId)){
        return StatusType(3);
    }
    AVLNode<Ship>*  targetShip = ship_head.find(shipId);
    return output_t<int>(targetShip->val->m_cannons); 
}

output_t<int> Ocean::get_richest_pirate(int shipId){
    if(shipId <= 0 ){
        return StatusType(2);
    }
    if(!ship_head.contains(shipId)){
        return StatusType(3);
    }
    AVLNode<Ship>*  targetShip = ship_head.find(shipId);
    if(!targetShip -> val->pirates_treasure.empty()){
        return StatusType(3);
    }
    return output_t<int>(targetShip->val->m_richestPirate->m_pirateId);
}

StatusType Ocean::ships_battle(int shipId1,int shipId2){
    if(shipId1 <= 0 || shipId2 <= 0 ){
        return StatusType(2);
    }
    if(!ship_head.contains(shipId1) || !ship_head.contains(shipId2)){
        return StatusType(3);
    }
    AVLNode<Ship>* target1 = ship_head.find(shipId1);
    AVLNode<Ship>* target2 = ship_head.find(shipId2);
    int combatPower1 = target1->val->m_cannons;
    if(combatPower1 > target1->val->pirates_id.getSize()){
        combatPower1 = target1->val->pirates_id.getSize();
    }
    int combatPower2 = target2->val->m_cannons;
    if(combatPower2 > target2->val->pirates_id.getSize()){
        combatPower2 = target2->val->pirates_id.getSize();
    }
    if(combatPower2 == combatPower1){
        return StatusType(0);
    }
    if(combatPower1 >= combatPower2){
        target1->val->m_battleWinnings+= target2->val->pirates_id.getSize();
        target2->val->m_battleWinnings-= target1->val->pirates_id.getSize();
        return StatusType(0);
    }
    if(combatPower2 >= combatPower1){
        target1->val->m_battleWinnings-= target2->val->pirates_id.getSize();
        target2->val->m_battleWinnings+= target1->val->pirates_id.getSize();
        return StatusType(0);
    }
    return StatusType(0);
}



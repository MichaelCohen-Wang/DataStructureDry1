#include "pirates24b1.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "AVLNode.h"


//pirate constr'
Pirate::Pirate(const int id, int treasure, int pirateIndex, int shipId):
m_pirateId(id), m_treasure(treasure), m_pirateIndex(pirateIndex),m_shipId(shipId),m_ship(nullptr){}


bool Pirate::operator<(Pirate other){
    if(m_pirateId < other.m_pirateId){
        //std::cout << m_pirateId << " < " << other.m_pirateId << std::endl ; 
        return true;
    }
    else{
        return false; 
    }
}

bool Pirate::operator>(Pirate other){
    if(m_pirateId > other.m_pirateId){
        //std::cout << m_pirateId << " > " << other.m_pirateId << std::endl ; 
        return true; 
    }
    else{
        return false; 
    }
}

bool Pirate::operator<=(Pirate other){
    if(m_treasure < other.m_treasure){
        //std::cout << m_pirateId << " < " << other.m_pirateId << std::endl ; 
        return true;
    
    }
    else if(m_treasure > other.m_treasure){
        return false; 
    }
    else{
        //std::cout << m_pirateId << " <1 " << other.m_pirateId << std::endl ; 
        return m_pirateId < other.m_pirateId;
    }
}

bool Pirate::operator>=(Pirate other){
    if(m_treasure > other.m_treasure){
        //std::cout << m_pirateId << " < " << other.m_pirateId << std::endl ; 
        return true;
    
    }
    else if(m_treasure < other.m_treasure){
        return false; 
    }
    else{
        //std::cout << m_pirateId << " <2 " << other.m_pirateId << std::endl ; 
        return m_pirateId > other.m_pirateId;
    }
}


//ship constr'
Ship::Ship(const int id, int cannons,int counter): 
  m_shipId(id), m_cannons(cannons), m_battleWinnings(0), m_counter(counter){}

bool Ship::operator<(Ship other){
    if(m_shipId < other.m_shipId){
        return true;
    }
    else{
        return false; 
    }
}

bool Ship::operator>(Ship other){
    if(m_shipId > other.m_shipId){
        return true; 
    }
    else{
        return false; 
    }
}

/*int Ship::exist(int id){

}
*/
Ocean::Ocean() = default; 

Ocean::~Ocean() = default; 

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

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure) {
  if (shipId <= 0 || pirateId <= 0) { // invalid input = 2
    return StatusType(2);
  }

  if (!ship_head.contains(shipId) || pirate_head.contains(pirateId)) // failure no such ship
    return StatusType(3);

  AVLNode<Ship>* current_ship = ship_head.find(shipId);

  if (current_ship->val.pirates_id.contains(pirateId)) {
    return StatusType(3); // already exists
  }

  // Create a single Pirate object and populate its data
  Pirate new_pirate(pirateId, &current_ship->val, treasure - current_ship->val.m_battleWinnings,
                    current_ship->val.m_currentIndex, current_ship->key);
  //new_pirate.m_ship = &current_ship->val; // assign pointer to the ship

  try {
    // Use a single Pirate object for insertions (avoid unnecessary copies)
    //the node itself uses the assignment for this, so there's no aliasing 
    AVLNode<Pirate>* pirateleaf = new AVLNode<Pirate>(pirateId, new_pirate);
    pirate_head.insert(pirateleaf);

    AVLNode<Pirate>* idPirate = new AVLNode<Pirate>(pirateId, new_pirate);
    current_ship->val.pirates_id.insert(idPirate);

    AVLNode<Pirate>* indexPirate = new AVLNode<Pirate>(current_ship->val.m_currentIndex, new_pirate);
    current_ship->val.pirates_index.insert(indexPirate);

    AVLNode<Pirate>* treasurePirate = new AVLNode<Pirate>(treasure, new_pirate);
    current_ship->val.pirates_treasure.insert(treasurePirate);

    //if (current_ship->val.m_counter == 0) {
      //std::cout << "I was here 40" << std::endl; 
      //std::cout << "address of ship : " << current_ship << std::endl; 
      //NEW PIRATE GETS DELETED, YOU NEED TO POINT TO THE NEW OBJECT IN THE NODES
      //current_ship->val.m_richestPirate = &current_ship->val.pirates_id.find(pirateId)->val;
      //std::cout << current_ship->val.m_richestPirate->m_pirateId << std::endl; 

    //} else {
      /*if (current_ship->val.m_richestPirate->m_treasure < treasure - current_ship->val.m_battleWinnings ||
          (current_ship->val.m_richestPirate->m_treasure == treasure - current_ship->val.m_battleWinnings &&
           current_ship->val.m_richestPirate->m_pirateId < pirateId)) {
        current_ship->val.m_richestPirate =  &current_ship->val.pirates_id.find(pirateId)->val;
      } */
    current_ship->val.m_richestPirate =  &current_ship->val.pirates_treasure.getMaximum()->val;
    //}

    current_ship->val.m_currentIndex++;
    current_ship->val.m_counter++;
    return StatusType(0); // success
  } catch (...) { // bad alloc allocation error=1
    return StatusType(1);
  }
}
/*
StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure){


    if(shipId <= 0 || pirateId <= 0){//invalid input =2
    return StatusType(2);
    }

    if(! (this->ship_head.contains(shipId)) || this->pirate_head.contains(pirateId))// failure no such ship
        return StatusType(3);

    AVLNode<Ship>* current_ship = this->ship_head.find(shipId);
   
    if(current_ship->val.pirates_id.contains(pirateId) ){
        return StatusType(3);  //already exist
    }
    Pirate new_pirate1 = Pirate(pirateId,treasure - current_ship->val.m_battleWinnings, current_ship->val.m_currentIndex,current_ship->key); //do we need to do a pointer
    new_pirate1.m_ship= &current_ship->val; //to have a pointer to the ship
    std::cout << "pirate 1 data: "<< new_pirate1.m_pirateId << std::endl; 
    Pirate new_pirate2 = new_pirate1;//for index
    Pirate new_pirate3 = new_pirate1;//for treasure
    Pirate new_pirate4 = new_pirate1;//for ocean
    std::cout << "pirate 4 data " <<new_pirate4.m_pirateId << std::endl; 


    try{  
        AVLNode<Pirate>* pirateleaf = new AVLNode<Pirate>(pirateId,new_pirate4);//for all the piraes in the ocean
        this->pirate_head.insert((pirateleaf));

        AVLNode<Pirate>* idPirate = new AVLNode<Pirate>(pirateId, new_pirate1);
        AVLNode<Pirate>* indexPirate = new AVLNode<Pirate>(current_ship->val.m_currentIndex, new_pirate2);
        AVLNode<Pirate>* treasurePirate = new AVLNode<Pirate>(treasure, new_pirate3);
        AVLNode<Pirate>* oceanPirate = new AVLNode<Pirate>(treasure, new_pirate4);
        current_ship->val.pirates_id.insert(idPirate);//add the pirates to the tree
        current_ship->val.pirates_index.insert(indexPirate);
        current_ship->val.pirates_treasure.insert(treasurePirate);
        pirate_head.insert(oceanPirate);
        if(current_ship->val.m_counter == 0){
            //no need to free because new_pirate4 wasn't dynmically allocated
            current_ship->val.m_richestPirate = &new_pirate4;
            std::cout << "i was here44 value: "<< current_ship->val.m_richestPirate->m_pirateId << std::endl; 
        }
        else{
            std::cout << "i was here 33"<< std::endl;
    
            std::cout << "pirateid val: " <<  current_ship->val.pirates_id.find(pirateId)->val.m_pirateId<<std::endl; 
            if(current_ship->val.m_richestPirate->m_treasure < treasure){
                current_ship->val.m_richestPirate = &new_pirate4;
            }
            else if(current_ship->val.m_richestPirate->m_treasure == treasure){
                if(current_ship->val.m_richestPirate->m_pirateId < pirateId){
                    current_ship->val.m_richestPirate = &new_pirate4;
                }
            }
        }
        //std::cout << "i was here 34"<< std::endl;
        current_ship->val.m_currentIndex ++;
        current_ship->val.m_counter++;
        //std::cout << "i was here 35"<< std::endl;
        return StatusType(0); //success  
    }
    catch (...){ // bad alloc allocation error=1
        return StatusType(1);
    }
    return StatusType(0);
}
*/  
StatusType Ocean::remove_pirate(int pirateId){
    if(pirateId <= 0){//invalid input =2
        return StatusType(2);
    }


    if(!this->pirate_head.contains(pirateId))// failure no such ship
        return StatusType(3);
    
    

    AVLNode<Pirate>* target = pirate_head.find(pirateId); 
    Ship* out = target->val.m_ship;
    //out->pirates_treasure.erase(target->val.m_treasure);
    out->m_richestPirate = nullptr; 

    out->pirates_treasure.erase(target->val);
    out->pirates_id.erase(target->val.m_pirateId);
    out->pirates_index.erase(target->val.m_pirateIndex);
    out->m_counter--; 
    if(out->m_counter > 0){
        out->m_richestPirate = &(out->pirates_treasure.getMaximum()->val);
    }
    pirate_head.erase(pirateId);
    return StatusType(0);
}
    
StatusType Ocean::treason(int sourceShipId, int destShipId){
    if(sourceShipId<= 0 || destShipId<= 0 || sourceShipId == destShipId){//invalid input =2
        return StatusType(2);
    }
    if(!this->ship_head.contains(sourceShipId) || !this->ship_head.contains(destShipId))// failure no such ship
        return StatusType(3);
        
    AVLNode<Ship>* sourceShip = this->ship_head.find(sourceShipId);
    AVLNode<Ship>* destShip = this->ship_head.find(destShipId);
    if(sourceShip->val.m_counter == 0){
        return StatusType(3);
    }

    AVLNode<Pirate>* oldest = sourceShip->val.pirates_index.getMinimum();
    AVLNode<Pirate>* oldestCash = pirate_head.find(oldest->val.m_pirateId);
    int oldestId = oldest->val.m_pirateId;
    int oldestTreasure = oldestCash->val.m_treasure + sourceShip->val.m_battleWinnings;

    remove_pirate(oldestId);

    add_pirate(oldestId, destShip->val.m_shipId, oldestTreasure);

    return StatusType(0);

}


StatusType Ocean::update_pirate_treasure(int pirateId, int change){
   if(pirateId <= 0){//invalid input =2
        //std::cout << "WHY AM I HERE" << std::endl;
        return StatusType(2);
    }

    if(! (this->pirate_head.contains(pirateId))) {// failure no such ship
        //std::cout << "WHY AM I HERE" << std::endl;
        return StatusType(3);
    }

    AVLNode<Pirate>* target = pirate_head.find(pirateId);
    
    if (target == nullptr) {
        return StatusType(3);
    }

    Ship* targetShip = target->val.m_ship;
    //targetShip->pirates_treasure.erase(target->val.m_treasure); 
    
    //targetShip->pirates_treasure.print(); 
    //Pirate test = target->val; 
    targetShip->pirates_treasure.erase(target->val); 

    target->val.m_treasure += change; 

    AVLNode<Pirate>* newNode = new AVLNode<Pirate>(target->val.m_treasure, target->val);
    targetShip->pirates_treasure.insert(newNode); 
//changed here may need to fix
    targetShip->m_richestPirate = &targetShip->pirates_treasure.getMaximum()->val;
/*
    if(targetShip->m_counter == 0){
        //no need to free because new_pirate4 wasn't dynmically allocated
        //std::cout << "Iwas here"<< std::endl; 
        targetShip->m_richestPirate = & (target->val);
    }
    else{
        if(targetShip->m_richestPirate->m_treasure < target->val.m_treasure){
            //std::cout << "Iwas here 3"<< std::endl; 
            targetShip->m_richestPirate = & (target->val);
        }
        else if(targetShip->m_richestPirate->m_treasure == target->val.m_treasure){
            if(targetShip->m_richestPirate->m_pirateId < pirateId){
                //std::cout << "Iwas here 2"<< std::endl; 
                targetShip->m_richestPirate = & (target->val);
            }
        }
    }
*/
    return StatusType(0);

}
/*
StatusType Ocean::update_pirate_treasure(int pirateId, int change){
   if(pirateId <= 0){//invalid input =2
        std::cout << "WHY AM I HERE" << std::endl;
        return StatusType(2);
    }

    if(! (this->pirate_head.contains(pirateId))) {// failure no such ship
        //std::cout << "WHY AM I HERE" << std::endl;
        return StatusType(3);
    }

    AVLNode<Pirate>* target = pirate_head.find(pirateId);
    
    Ship* targetShip = target->val.m_ship;

    targetShip->pirates_treasure.erase(target->val.m_treasure); 
    target->val.m_treasure += change; 
    Pirate newPirate = Pirate(target->val.m_pirateId, target->val.m_treasure, target->val.m_pirateIndex, target->val.m_shipId);
    newPirate.m_ship = targetShip; 
    AVLNode<Pirate>* newNode = new AVLNode<Pirate>(newPirate.m_treasure, newPirate);
    targetShip->pirates_treasure.insert(newNode); 

    if(targetShip->m_counter == 0){
        //no need to free because new_pirate4 wasn't dynmically allocated
        targetShip->m_richestPirate = &newPirate;
    }
    else{
        if(targetShip->m_richestPirate->m_treasure < target->val.m_treasure){
            targetShip->m_richestPirate = &newPirate;
        }
        else if(targetShip->m_richestPirate->m_treasure == target->val.m_treasure){
            if(targetShip->m_richestPirate->m_pirateId < pirateId){
                targetShip->m_richestPirate = &newPirate;
            }
        }
    }
    return StatusType(0);


}
*/

output_t<int> Ocean::get_treasure(int pirateId){
    if(pirateId <= 0){
        return StatusType(2);
    }
    if(!pirate_head.contains(pirateId)){
        return StatusType(3);
    }
    AVLNode<Pirate>* targetPirate = pirate_head.find(pirateId);
    Ship* current_ship = targetPirate->val.m_ship; 

    //add winnings gained in fights
    return output_t<int>(targetPirate->val.m_treasure + current_ship->m_battleWinnings); 
}


output_t<int> Ocean::get_cannons(int shipId){
    if(shipId <= 0 ){
        return StatusType(2);
    }
    if(!ship_head.contains(shipId)){
        return StatusType(3);
    }
    AVLNode<Ship>*  targetShip = ship_head.find(shipId);
    return output_t<int>(targetShip->val.m_cannons); 
}

output_t<int> Ocean::get_richest_pirate(int shipId){

    if(shipId <= 0 ){
        //std::cout<< "error1"<<std::endl; 
        return StatusType(2);
    }
    if(!ship_head.contains(shipId)){
        //std::cout<< "error2"<<std::endl; 
        return StatusType(3);
    }

    AVLNode<Ship>*  targetShip = ship_head.find(shipId);
    
    if(targetShip->val.m_counter == 0){
        //std::cout<< "error3"<<std::endl; 
        return StatusType(3);
    }
    
    
    //std::cout << "richest pirate current ship " << targetShip << std::endl;
    //std::cout << "richest pirate current ship " << targetShip->val.m_richestPirate->m_treasure << std::endl;  
    //std::cout << "print pirate id: " << targetShip->val.m_richestPirate->m_pirateId << std::endl;
    return output_t<int>(targetShip->val.m_richestPirate->m_pirateId);
}

StatusType Ocean::ships_battle(int shipId1,int shipId2){
    if(shipId1 <= 0 || shipId2 <= 0 || shipId1 == shipId2){
        return StatusType(2);
    }
    if(!ship_head.contains(shipId1) || !ship_head.contains(shipId2)){
        return StatusType(3);
    }

    AVLNode<Ship>* target1 = ship_head.find(shipId1);
    AVLNode<Ship>* target2 = ship_head.find(shipId2);
    int combatPower1 = target1->val.m_cannons;
    if(combatPower1 > target1->val.m_counter){
        combatPower1 = target1->val.m_counter;
    }
    int combatPower2 = target2->val.m_cannons;
    if(combatPower2 > target2->val.m_counter){
        combatPower2 = target2->val.m_counter;
    }
    if(combatPower2 == combatPower1){
        return StatusType(0);
    }
    if(combatPower1 >= combatPower2){
        target1->val.m_battleWinnings+= target2->val.m_counter;
        target2->val.m_battleWinnings-= target1->val.m_counter;
        return StatusType(0);
    }
    if(combatPower2 >= combatPower1){
        target1->val.m_battleWinnings-= target2->val.m_counter;
        target2->val.m_battleWinnings+= target1->val.m_counter;
        return StatusType(0);
    }
    return StatusType(0);
}





// 
// 234218 Data Structures 1.
// Semester: 2024B (spring).
// Wet Exercise #1.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "AVLNode.h"
#include "AVLTree.h"
#include "pirates24b1.h"
#include <string>
#include <iostream>
#include "wet1util.h"

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);

void printStatus(StatusType status) {
    switch (status) {
        case StatusType::SUCCESS:
            std::cout << "SUCCESS" << std::endl;
            break;
        case StatusType::ALLOCATION_ERROR:
            std::cout << "ALLOCATION_ERROR" << std::endl;
            break;
        case StatusType::INVALID_INPUT:
            std::cout << "INVALID_INPUT" << std::endl;
            break;
        case StatusType::FAILURE:
            std::cout << "FAILURE" << std::endl;
            break;
        default:
            std::cout << "UNKNOWN_STATUS" << std::endl;
    }
}

void testTreasure(Ocean &ocean, int pirateId, int expectedTreasure) {
    auto result = ocean.get_treasure(pirateId);
    if (result.status() == StatusType::SUCCESS && result.ans() == expectedTreasure) {
        std::cout << "Treasure check for pirate " << pirateId << ": PASS" << std::endl;
    } else {
        std::cout << "Treasure check for pirate " << pirateId << ": FAIL" << std::endl;
    }
}

void testCannons(Ocean &ocean, int shipId, int expectedCannons) {
    auto result = ocean.get_cannons(shipId);
    if (result.status() == StatusType::SUCCESS && result.ans() == expectedCannons) {
        std::cout << "Cannons check for ship " << shipId << ": PASS" << std::endl;
    } else {
        std::cout << "Cannons check for ship " << shipId << ": FAIL" << std::endl;
    }
}

void testRichestPirate(Ocean &ocean, int shipId, int expectedPirateId) {
    auto result = ocean.get_richest_pirate(shipId);
    if (result.status() == StatusType::SUCCESS && result.ans() == expectedPirateId) {
        std::cout << "Richest pirate check for ship " << shipId << ": PASS" << std::endl;
    } else {
        std::cout << "Richest pirate check for ship " << shipId << ": FAIL" << std::endl;
    }
}

int main() {
    Ocean ocean;

    //std::cout << "-------------------------- Add Ship Tests --------------------------" << std::endl;
    // Test add_ship
    printStatus(ocean.add_ship(1, 10));  // Should print SUCCESS
    printStatus(ocean.add_ship(2, 20));  // Should print SUCCESS
    printStatus(ocean.add_ship(1, 15));  // Should print FAILURE (duplicate shipId)
    printStatus(ocean.add_ship(-1, 15)); // Should print INVALID_INPUT
    printStatus(ocean.add_ship(3, -10)); // Should print INVALID_INPUT

    //std::cout << "-------------------------- Add Pirate Tests --------------------------" << std::endl;
    // Test add_pirate
    
    //seg fault here
    printStatus(ocean.add_pirate(101, 1, 100));  // Should print SUCCESS
    std::cout << ocean.get_richest_pirate(1).ans() << std::endl; 
    printStatus(ocean.add_pirate(102, 1, 150));  // Should print SUCCESS
    

    printStatus(ocean.add_pirate(101, 2, 200));  // Should print FAILURE (duplicate pirateId)
    printStatus(ocean.add_pirate(-1, 2, 200));   // Should print INVALID_INPUT
    printStatus(ocean.add_pirate(103, 3, 200));  // Should print FAILURE (shipId not found)
    
    //std::cout << "-------------------------- Get Treasure Tests --------------------------" << std::endl;
    // Test get_treasure
/*
    auto treasure1 = ocean.get_treasure(101);
    if (treasure1.status() == StatusType::SUCCESS) {
        std::cout << "Pirate 101 Treasure: " << treasure1.ans() << std::endl;  // Should print 100
    } else {
        printStatus(treasure1.status());
    }

    auto treasure2 = ocean.get_treasure(-1);
    if (treasure2.status() == StatusType::SUCCESS) {
        std::cout << "Pirate -1 Treasure: " << treasure2.ans() << std::endl;  // Should not print
    } else {
        printStatus(treasure2.status());  // Should print INVALID_INPUT
    }

    //std::cout << "-------------------------- Get Cannons Tests --------------------------" << std::endl;
    // Test get_cannons
    auto cannons1 = ocean.get_cannons(1);
    if (cannons1.status() == StatusType::SUCCESS) {
        std::cout << "Ship 1 Cannons: " << cannons1.ans() << std::endl;  // Should print 10
    } else {
        printStatus(cannons1.status());
    }

    auto cannons2 = ocean.get_cannons(3);
    if (cannons2.status() == StatusType::SUCCESS) {
        std::cout << "Ship 3 Cannons: " << cannons2.ans() << std::endl;  // Should not print
    } else {
        printStatus(cannons2.status());  // Should print FAILURE
    }

    //std::cout << "-------------------------- Remove Pirate Tests --------------------------" << std::endl;
    // Test remove_pirate
    printStatus(ocean.remove_pirate(101));  // Should print SUCCESS
    printStatus(ocean.remove_pirate(101));  // Should print FAILURE (pirateId not found)
    printStatus(ocean.remove_pirate(-1));   // Should print INVALID_INPUT

    //std::cout << "-------------------------- Remove Ship Tests --------------------------" << std::endl;
    // Test remove_ship
    printStatus(ocean.remove_ship(1));  // Should print FAILURE (pirates still on the ship)
    printStatus(ocean.remove_ship(2));  // Should print SUCCESS
    printStatus(ocean.remove_ship(3));  // Should print FAILURE (shipId not found)
    printStatus(ocean.remove_ship(-1)); // Should print INVALID_INPUT

    //std::cout << "-------------------------- Ships Battle Tests --------------------------" << std::endl;
    // Test ships_battle
    printStatus(ocean.add_ship(4, 30));  // Add new ship for battle testing
    printStatus(ocean.add_ship(5, 25));  // Add new ship for battle testing
    printStatus(ocean.add_pirate(104, 4, 300));  // Add pirates for battle testing
    printStatus(ocean.add_pirate(105, 5, 250));  // Add pirates for battle testing
    printStatus(ocean.ships_battle(4, 5));  // Should print SUCCESS
    printStatus(ocean.ships_battle(4, 6));  // Should print FAILURE (shipId not found)
    printStatus(ocean.ships_battle(6, 5));  // Should print FAILURE (shipId not found)
    printStatus(ocean.ships_battle(4, 4));  // Should print INVALID_INPUT
    printStatus(ocean.ships_battle(-1, 5)); // Should print INVALID_INPUT
    printStatus(ocean.ships_battle(4, -1)); // Should print INVALID_INPUT

    //std::cout << "-------------------------- Treason Tests --------------------------" << std::endl;
    // Test treason
    printStatus(ocean.add_ship(6, 40));  // Add new ship for treason testing
    printStatus(ocean.add_pirate(106, 4, 350));  // Add pirates for treason testing
    printStatus(ocean.treason(4, 6));    // Should print SUCCESS
    printStatus(ocean.treason(4, 7));    // Should print FAILURE (shipId not found)
    printStatus(ocean.treason(7, 6));    // Should print FAILURE (shipId not found)
    printStatus(ocean.treason(4, 4));    // Should print INVALID_INPUT
    printStatus(ocean.treason(-1, 6));   // Should print INVALID_INPUT
    printStatus(ocean.treason(4, -1));   // Should print INVALID_INPUT

    //std::cout << "-------------------------- Update Pirate Treasure Tests --------------------------" << std::endl;
    // Test update_pirate_treasure
    printStatus(ocean.update_pirate_treasure(102, 50));  // Should print SUCCESS
    testTreasure(ocean, 102, 200); // Expected treasure: 150 + 50 = 200
    printStatus(ocean.update_pirate_treasure(102, -100)); // Should print SUCCESS
    testTreasure(ocean, 102, 100); // Expected treasure: 200 - 100 = 100
    printStatus(ocean.update_pirate_treasure(-1, 50));   // Should print INVALID_INPUT
    printStatus(ocean.update_pirate_treasure(999, 50));  // Should print FAILURE (pirateId not found)

    //std::cout << "------------------------ Get Richest Pirate Tests --------------------------" << std::endl;
    // Test get_richest_pirate

    auto richestPirate = ocean.get_richest_pirate(1);
    if (richestPirate.status() == StatusType::SUCCESS) {
        std::cout << "Richest Pirate on Ship 1: " << richestPirate.ans() << std::endl;
    } else {
        printStatus(richestPirate.status());
    }

    auto richestPirate2 = ocean.get_richest_pirate(6);
    if (richestPirate2.status() == StatusType::SUCCESS) {
        std::cout << "Richest Pirate on Ship 6: " << richestPirate2.ans() << std::endl;
    } else {
        printStatus(richestPirate2.status());
    }

    //std::cout << "-------------------------- Data Validation Tests --------------------------" << std::endl;
    // Validate data correctness
    
    testTreasure(ocean, 102, 100); // Expected treasure after updates
    testCannons(ocean, 1, 10);     // Expected cannons for ship 1
    testCannons(ocean, 2, 20);     // Expected cannons for ship 2
    testRichestPirate(ocean, 1, 102); // Expected richest pirate on ship 1
    */
    return 0;
}

/*
int main()
{



    AVLNode<int>* node1 = new AVLNode<int>(20, 20);
    AVLNode<int>* node2 = new AVLNode<int>(30, 20);
    AVLNode<int>* node3 = new AVLNode<int>(10, 20);
    AVLNode<int>* node4 = new AVLNode<int>(5, 20);
    AVLNode<int>* node5 = new AVLNode<int>(11, 20);
    
    AVLTree<int> tree; 
    tree.insert(node1);
    tree.insert(node2);
    tree.insert(node3);
    tree.insert(node4);
    tree.insert(node5);

    tree.erase(20);

    std::cout << tree.root -> key << std::endl;
    std::cout << tree.root -> leftNode -> key << std::endl;
    std::cout << tree.root -> rightNode -> key << std::endl;

    int d1, d2, d3;

    // Init
    Ocean *obj = new Ocean();
    
    // Execute all commands in file
    string op;

    while (cin >> op)
    {
        if (!op.compare("add_ship")) {
            cin >> d1 >> d2;
            print(op, obj->add_ship(d1, d2));
        } else if (!op.compare("remove_ship")) {
            cin >> d1;
            print(op, obj->remove_ship(d1));
        } else if (!op.compare("add_pirate")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->add_pirate(d1, d2, d3));
        } else if (!op.compare("remove_pirate")) {
            cin >> d1;
            print(op, obj->remove_pirate(d1));
        } else if (!op.compare("treason")) {
            cin >> d1 >> d2;
            print(op, obj->treason(d1, d2));
        } else if (!op.compare("update_pirate_treasure")) {
            cin >> d1 >> d2;
            print(op, obj->update_pirate_treasure(d1, d2));
        } else if (!op.compare("get_treasure")) {
            cin >> d1;
            print(op, obj->get_treasure(d1));
        } else if (!op.compare("get_cannons")) {
            cin >> d1;
            print(op, obj->get_cannons(d1));
        } else if (!op.compare("get_richest_pirate")) {
            cin >> d1;
            print(op, obj->get_richest_pirate(d1));
        } else if (!op.compare("ships_battle")) {
            cin >> d1 >> d2;
            print(op, obj->ships_battle(d1, d2));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit 
    delete obj;

    return 0;
}
*/


// Helpers
static const char *StatusTypeStr[] =
{
    "SUCCESS",
    "ALLOCATION_ERROR",
    "INVALID_INPUT",
    "FAILURE"
};

void print(string cmd, StatusType res) 
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

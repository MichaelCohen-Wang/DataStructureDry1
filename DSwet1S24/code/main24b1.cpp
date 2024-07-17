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


int main()
{
    /*

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

*/
    
    Ocean ocean;

    // Test add_ship
    printStatus(ocean.add_ship(1, 10));  // Should print SUCCESS
    printStatus(ocean.add_ship(2, 15));  // Should print SUCCESS
    printStatus(ocean.add_ship(1, 20));  // Should print FAILURE (duplicate shipId)

    // Test add_pirate
    printStatus(ocean.add_pirate(101, 1, 100));  // Should print SUCCESS
    printStatus(ocean.add_pirate(102, 1, 150));  // Should print SUCCESS
    printStatus(ocean.add_pirate(101, 2, 200));  // Should print FAILURE (duplicate pirateId)


    // Test get_treasure
    auto treasure1 = ocean.get_treasure(101);
    if (treasure1.status() == StatusType::SUCCESS) {
        std::cout << "Pirate 101 Treasure: " << treasure1.ans() << std::endl;  // Should print 100
    } else {
        printStatus(treasure1.status());
    }
    // Test get_cannons
    auto cannons1 = ocean.get_cannons(1);
    if (cannons1.status() == StatusType::SUCCESS) {
        std::cout << "Ship 1 Cannons: " << cannons1.ans() << std::endl;  // Should print 10
    } else {
        printStatus(cannons1.status());
    }
 /*
    // Test remove_pirate
    printStatus(ocean.remove_pirate(101));  // Should print SUCCESS
    printStatus(ocean.remove_pirate(101));  // Should print FAILURE (pirateId not found)

    // Test remove_ship
    printStatus(ocean.remove_ship(1));  // Should print FAILURE (pirates still on the ship)
    printStatus(ocean.remove_ship(2));  // Should print SUCCESS
*/
    std::cout << "battle test: " << std::endl; 
    printStatus(ocean.ships_battle(1, 2));  // Should print SUCCESS
    //failed

    // Test treason
    std::cout << "treason test: " << std::endl; 
    printStatus(ocean.treason(1, 2));  // Should print SUCCESS

    // Test update_pirate_treasure
    std::cout << "Update treasure: " << std::endl; 
    printStatus(ocean.update_pirate_treasure(102, 50));  // Should print SUCCESS
    //fail fefffffffffff

    // Test get_richest_pirate
    auto richestPirate = ocean.get_richest_pirate(1);
    if (richestPirate.status() == StatusType::SUCCESS) {
        std::cout << "Richest Pirate on Ship 1: " << richestPirate.ans() << std::endl;
    } else {
        printStatus(richestPirate.status());
    }
/*
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
*/
    return 0;

}

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

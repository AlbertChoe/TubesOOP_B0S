#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Inventory.hpp"
#include <iostream>
using namespace std;

class Player {
protected:
    string name;
    int weight;
    int gulden;
    Inventory inventory;
public:
    void eat();
    void displayInventory();
    virtual int getTaxable() = 0;
};

#endif
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Inventory.hpp"
#include "Store.hpp"
#include "Taxable.hpp"
#include <iostream>
using namespace std;

class Player: public Taxable {
protected:
    string name;
    int weight;
    int gulden;
    Inventory inventory;
public:
    void eat();
    void displayInventory();
    void buy(Store& store);
    void sell(Store& store);
};

#endif
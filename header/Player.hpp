#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Inventory.hpp"
#include "Store.hpp"
#include "Exception.hpp"
#include "Config.hpp"
#include <iostream>
using namespace std;

enum class PlayerType {
    Mayor,
    Farmer,
    Breeder
};

class Player {
protected:
    string name;
    int weight;
    int gulden;
    Inventory inventory;
public:
    Player(string name, int InventoryRow, int InventoryCol): name(name), gulden(50), weight(40), inventory(InventoryRow,InventoryCol){}
    Player(string name, int gulden,int weight, int InventoryRow, int InventoryCol): name(name), gulden(gulden), weight(weight), inventory(InventoryRow,InventoryCol){}
    string getName();
    int getWeight();
    int getGulden();
    Inventory& getRefInventory();
    void setName(string _name);
    void setGulden(int gulden);
    void eat();
    void displayInventory();
    virtual PlayerType getType() = 0;
    virtual int getTaxable() = 0;
};

#endif
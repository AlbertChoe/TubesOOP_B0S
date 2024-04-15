#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Inventory.hpp"
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
    int gulden;
    int weight;
    Inventory inventory;
public:
    Player(string name, int InventoryRow, int InventoryCol): name(name), gulden(50), weight(40), inventory(InventoryRow, InventoryCol) {}
    Player(string name, int weight,int gulden, int InventoryRow, int InventoryCol): name(name), gulden(gulden), weight(weight), inventory(InventoryRow, InventoryCol) {}
    string getName();
    int getWeight();
    int getGulden();
    Inventory& getRefInventory();
    void setRefInventory(Inventory);
    void setName(string _name);
    void setGulden(int gulden);
    void setWeight(int weight);
    void eat();
    void displayInventory();
    virtual shared_ptr<Player> normalizeClone(int _gulden, int _weight) = 0;
    friend bool operator==(const Player& lhs, const Player& rhs);
    virtual PlayerType getType() = 0;
    virtual int getTaxable() = 0;
};

#endif
#ifndef FARMER_HPP
#define FARMER_HPP

#include "Field.hpp"
#include "Player.hpp"
#include <iostream>
using namespace std;

class Farmer : public Player {
private:
    Field field;
public:
    Farmer( string name, int InventoryRow, int InventoryCol, int fieldRow, int fieldCol): Player(name,InventoryRow,InventoryCol), field(fieldRow, fieldCol) {}
    Farmer( string name, int weight, int gulden, int InventoryRow, int InventoryCol, int fieldRow, int fieldCol): Player(name, weight, gulden, InventoryRow, InventoryCol), field(fieldRow, fieldCol) {}
    void plantCrop();
    void displayField();
    void harvestCrop();
    int getTaxable();
    PlayerType getType();
    Field& getRefField();
};

#endif
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
    Farmer( string name, int fieldRow, int fieldCol): Player(name), field(fieldRow, fieldCol) {}
    Farmer( string name, int weight, int gulden, int fieldRow, int fieldCol): Player(name, weight, gulden), field(fieldRow, fieldCol) {}
    string getType() const override { return "Petani"; }
    void plantCrop();
    void displayField();
    void harvestCrop();
    int getTaxable();
    // map<string, int> countReadyToHarvest();
};

#endif
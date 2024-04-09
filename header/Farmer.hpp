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
    void plantCrop();
    void displayField();
    void harvestCrop();
    int getTaxable();
    PlayerType getType();
    // map<string, int> countReadyToHarvest();
};

#endif
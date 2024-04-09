#ifndef BREEDER_HPP
#define BREEDER_HPP

#include "Barn.hpp"
#include "Player.hpp"
#include <iostream>
#include <map>
using namespace std;

class Breeder : public Player {
private:
    Barn barn;
public:
    void addLivestock();
    void feedLivestock();
    void harvestLivestock();
    void displayBarn();
    int getTaxable();
    PlayerType getType();
    // map<string, int> countReadyToHarvest();
};

#endif
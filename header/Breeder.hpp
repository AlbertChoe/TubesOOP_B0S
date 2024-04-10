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
    Breeder(string name, int barnRow, int barnCol): Player(name), barn(barnRow, barnCol) {}
    Breeder(string name, int weight, int gulden, int barnRow, int barnCol): Player(name, weight, gulden), barn(barnRow, barnCol) {}
    void addLivestock();
    void feedLivestock();
    void harvestLivestock();
    void displayBarn();
    int getTaxable();
    PlayerType getType();
};

#endif
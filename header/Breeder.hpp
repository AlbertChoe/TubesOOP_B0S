#ifndef BREEDER_HPP
#define BREEDER_HPP

#include "Barn.hpp"
#include "Player.hpp"
#include <iostream>
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
};

#endif
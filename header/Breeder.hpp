#include <iostream>
#include "Barn.hpp"
using namespace std;

#ifndef BREEDER_HPP
#define BREEDER_HPP

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
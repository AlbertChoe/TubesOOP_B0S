#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP

#include "Livestock.hpp"
using namespace std;

class Carnivore : public Livestock {
public:
    void eat(Consumable food);
};

#endif
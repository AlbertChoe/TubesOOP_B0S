#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP

#include "Livestock.hpp"
using namespace std;

class Herbivore : public Livestock {
public:
    void eat(Consumable food);
};

#endif
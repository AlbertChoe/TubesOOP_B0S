#ifndef OMNIVORE_HPP
#define OMNIVORE_HPP

#include "Livestock.hpp"
using namespace std;

class Omnivore : public Livestock {
public:
    void eat(Consumable food);
};

#endif
#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP

#include "Livestock.hpp"
using namespace std;

class Herbivore : public Livestock {
public:
    // Constructor default
    Herbivore();
    // Constructor user defined
    Herbivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight);
    // Destructor
    ~Herbivore();
    // Copy Constructor
    Herbivore(const Herbivore& herbivore);
    // Herbivore eat mechanism
    void eat(Consumable food);
};

#endif
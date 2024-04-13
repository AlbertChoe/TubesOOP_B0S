#ifndef OMNIVORE_HPP
#define OMNIVORE_HPP

#include "Livestock.hpp"
using namespace std;

class Omnivore : public Livestock {
public:
    // Constructor default
    Omnivore();
    // Constructor user defined
    Omnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight);
    // Destructor
    ~Omnivore();
    // Copy Constructor
    Omnivore(const Omnivore& omnivore);
    // Carnivore eat mechanism
    void eat(Consumable food);
    // Add new harvest results
    // vector<Consumable> harvest(ConsumableConfig configConsumable);
};

#endif
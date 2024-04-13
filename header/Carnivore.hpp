#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP

#include "Livestock.hpp"
#include "Config.hpp"
using namespace std;

class Carnivore : public Livestock {
public:
    // Constructor default
    Carnivore();
    // Constructor user defined
    Carnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight);
    // Destructor
    ~Carnivore();
    // Copy Constructor
    Carnivore(const Carnivore& carnivore);
    // Carnivore eat mechanism
    void eat(Consumable food);
    // Add new harvest results
    // vector<Consumable> harvest(ConsumableConfig configConsumable);
};

#endif
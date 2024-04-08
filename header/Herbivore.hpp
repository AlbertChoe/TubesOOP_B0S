#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP

#include "Livestock.hpp"
#include "Config.hpp"
using namespace std;

class Herbivore : public Livestock {
public:
    // Constructor default
    Herbivore();
    // Constructor user defined
    Herbivore(int id, string code, string name, string type, int price, int currentWeight, LivestockConfig livestockConfig);
    // Destructor
    ~Herbivore();
    // Copy Constructor
    Herbivore(const Herbivore& herbivore);
    // Herbivore eat mechanism
    void eat(Consumable food, ConsumableConfig consumableConfig);
    // Add new harvest results
    vector<Consumable> harvest(ConsumableConfig configConsumable, LivestockConfig livestockConfig);
};

#endif
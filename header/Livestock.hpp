#ifndef LIVESTOCK_HPP
#define LIVESTOCK_HPP

#include "Item.hpp"
#include "Consumable.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Livestock : public Item
{
private:
    int currentWeight;
    int harvestWeight;
    vector<Consumable> harvestResult;

public:
    // Constructor default
    Livestock();
    // Constructor user defined
    Livestock(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight);
    // Destructor
    ~Livestock();
    // Copy Constructor
    Livestock(const Livestock& livestock);
    // Getter
    int getHarvestWeight();
    int getCurrentWeight();
    vector<Consumable> getHarvestResult();
    // Setter
    void setHarvestWeight(int harvestWeight);
    void setCurrentWeight(int currentWeight);
    void setHarvestResult(vector<Consumable>& harvestResult);
    void addHarvestResult(Consumable result);
    // Eat Mechanism
    void addCurrentWeight(int weight) {
        this->setCurrentWeight(this->getCurrentWeight() + weight);
    }
    virtual void eat(Consumable food) = 0;
    // Display livestock code. Red if unfinished, Green if finished
    friend ostream& operator<<(ostream& os, const Livestock& livestock);
    // Checking if livestock is ready to harvest
    bool isReadyToHarvest();
    ItemType getItemType();
    bool isOmnivore() const {
        return type == "OMNIVORE";
    }
};

#endif
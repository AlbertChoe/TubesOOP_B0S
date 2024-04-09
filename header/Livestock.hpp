#ifndef LIVESTOCK_HPP
#define LIVESTOCK_HPP

#include "Item.hpp"
#include "Consumable.hpp"
#include "Config.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Livestock : public Item
{
private:
    int harvestWeight;
    int currentWeight;
    vector<Consumable> harvestResult;

public:
    // Constructor default
    Livestock();
    // Constructor user defined from config
    Livestock(int id, string code, string name, string type, int price, int currentWeight, LivestockConfig livestockConfig);
    // Constructor user defined
    Livestock(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight);
    // Destructor
    ~Livestock();
    // Copy Constructor
    Livestock(const Livestock& livestock);
    // Getter
    int getHarvestWeight();
    int getHarvestWeightFromConfig(string code, LivestockConfig configLivestock);
    int getCurrentWeight();
    vector<Consumable> getHarvestResult();
    // Setter
    void setHarvestWeight(int harvestWeight);
    void setCurrentWeight(int currentWeight);
    void setHarvestResult(vector<Consumable>& harvestResult);
    void addHarvestResult(Consumable result);
    // Eat Mechanism
    void eat(int weight);
    // Add new harvest results
    vector<Consumable> harvest(Consumable newHarvestResult);
    // Display livestock code. Red if unfinished, Green if finished
    friend ostream& operator<<(ostream& os, const Livestock& livestock);
    // Checking if livestock is ready to harvest
    bool isReadyToHarvest();
};

#endif
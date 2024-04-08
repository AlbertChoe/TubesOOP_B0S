#ifndef CROP_HPP
#define CROP_HPP

#include "Item.hpp"
#include "Consumable.hpp"
#include "Config.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Crop : public Item {
private:
    int currentDuration;
    int harvestDuration;
    vector<Consumable> harvestResult;
public:
    // Constructor default
    Crop();
    // Constructor user defined
    Crop(int id, string code, string name, string type, int price, int currentDuration, CropConfig cropConfig);
    // Destructor
    ~Crop();
    // Copy constructor
    Crop(const Crop& other);
    // Getter
    int getCurrentDuration();
    int getHarvestDuration(string code, CropConfig configCrop);
    vector<Consumable> getHarvestResult();
    // Setter
    void setCurrentDuration(int currentDuration);
    void setHarvestDuration(int harvestDuration);
    void setHarvestResult(vector<Consumable>& harvestResult);
    // Increment current duration
    void incrementDuration();
    // Add new harvest results
    vector<Consumable> harvest(ConsumableConfig consumableConfig);
    // Display code. Red for unfinished, Green for finisihed
    friend ostream& operator<<(ostream& os, const Crop& crop);
    // Checking if livestock is ready to harvest
    bool isReadyToHarvest();
};

#endif
#ifndef LIVESTOCK_HPP
#define LIVESTOCK_HPP

#include "Item.hpp"
#include "Consumable.hpp"
#include "Crop.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Livestock : public Item {
private:
    int harvestWeight;
    vector<Consumable> harvestResult;
public:
    virtual void eat(int weight);
    friend ostream& operator<<(ostream& os, const Crop& livestock);
};

#endif
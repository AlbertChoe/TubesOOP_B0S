#ifndef LIVESTOCK_HPP
#define LIVESTOCK_HPP

#include "Item.hpp"
#include "Consumable.hpp"
#include "iostream"
using namespace std;

class Livestock : public Item {
private:
    int harvestWeight;
public:
    void eat(Consumable food);
    friend ostream& operator<<(ostream& os, const Crop& livestock);
};

#endif
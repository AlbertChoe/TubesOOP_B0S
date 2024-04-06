#include <iostream> 
#include <map>
#include "Item.hpp"
using namespace std;

#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

class Consumable : public Item {
private:
    string origin;
    int addedWeight;
public:
};


#endif
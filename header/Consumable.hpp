#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "Item.hpp"
#include <iostream> 
#include <map>
using namespace std;


class Consumable : public Item {
private:
    string origin;
    int addedWeight;
public:
};


#endif
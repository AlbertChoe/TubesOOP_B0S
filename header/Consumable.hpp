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
    // Constructor
    Consumable();
    //Constructor user defined
    Consumable(int id, string code, string name, string type, int price, string origin, int addedWeight);
    // Destructor
    ~Consumable();
    // Copy Constructor
    Consumable(const Consumable& consumable);
    // Getter
    string getOrigin();
    int getAddedWeight();
    // Setter
    void setOrigin(string origin);
    void setAddedWeight(int addedWeight);
    ItemType getItemType();
};


#endif
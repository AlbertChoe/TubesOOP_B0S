#include <iostream> 
#include <map>
#include "Item.hpp"
using namespace std;

#ifndef BUILDING_HPP
#define BUILDING_HPP

class Building: public Item {
private:
    int id;
    string code;
    string name;
    int price;
    map<string, int> material;
public:
};

#endif
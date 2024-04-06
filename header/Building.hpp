#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Item.hpp"
#include <iostream> 
#include <map>
using namespace std;

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
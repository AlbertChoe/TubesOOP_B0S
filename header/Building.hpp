#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Item.hpp"
#include <iostream> 
#include <map>
using namespace std;

class Building: public Item {
private:
    map<string, int> material;
public:
    // Constructor
    Building();
    // Constructor user defined
    Building(int id, string code, string name, string type, int price);
    // Destructor
    ~Building();
    // Copy constructor
    Building(const Building& building);
    // Getter 
    map<string, int> getMaterial();
    // Setter
    void setMaterial(map<string, int> material);
    // Add material
    void addMaterial(string code, int count);
    int getCountMaterial(string code);
};

#endif
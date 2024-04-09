#include "../../header/Building.hpp"
using namespace std;

Building::Building() : Item(), material() {}

Building::Building(int id, string code, string name, string type, int price) : Item(id, code, name, type, price) {}

Building::~Building() {}

Building::Building(const Building& building) : Item(building), material(building.material) {}

map<string, int> Building::getMaterial(){
    return material;
}

void Building::setMaterial(map<string, int> material){
    this->material = material;
}

void Building::addMaterial(string code, int count) {
    if (material.find(code) != material.end()) {
        material[code] += count;
    } 
    else{
        material.insert({code, count});
    }
}

int Building::getCountMaterial(string code) {
    if (material.find(code) != material.end()) {
        return material[code];
    }
    return 0;
}
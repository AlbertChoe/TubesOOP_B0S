#include <iostream>
#include "Item.hpp"
using namespace std;

#ifndef CROP_HPP
#define CROP_HPP

class Crop : public Item {
private:
    int harvestDuration;
public:
    void incrementDuration();
    friend ostream& operator<<(ostream& os, const Crop& crop);
};




#endif
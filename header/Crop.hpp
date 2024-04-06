#ifndef CROP_HPP
#define CROP_HPP

#include "Item.hpp"
#include <iostream>
using namespace std;

class Crop : public Item {
private:
    int harvestDuration;
public:
    void incrementDuration();
    friend ostream& operator<<(ostream& os, const Crop& crop);
};

#endif